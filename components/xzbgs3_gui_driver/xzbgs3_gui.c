#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_touch_gt911.h"
#include "st7701s.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

#include "ui.h"
#include "idle_manager.h"

#define TAG "XZBGS3_GUI"

lv_indev_t * indev_touch = NULL;

#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (18 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL

#define EXAMPLE_PIN_NUM_BK_LIGHT       (1)

#define EXAMPLE_PIN_NUM_PCLK     (41)
#define EXAMPLE_PIN_NUM_DE       (40)
#define EXAMPLE_PIN_NUM_VSYNC    (39)
#define EXAMPLE_PIN_NUM_HSYNC    (38)

#define EXAMPLE_PIN_NUM_DATA0    (0)  // B0
#define EXAMPLE_PIN_NUM_DATA1    (45)  // B1
#define EXAMPLE_PIN_NUM_DATA2    (48)  // B2
#define EXAMPLE_PIN_NUM_DATA3    (47)  // B3
#define EXAMPLE_PIN_NUM_DATA4    (21)  // B4
#define EXAMPLE_PIN_NUM_DATA5    (14)  // G0
#define EXAMPLE_PIN_NUM_DATA6    (13)  // G1
#define EXAMPLE_PIN_NUM_DATA7    (12)  // G2
#define EXAMPLE_PIN_NUM_DATA8    (11)  // G3
#define EXAMPLE_PIN_NUM_DATA9    (10)  // G4
#define EXAMPLE_PIN_NUM_DATA10   (9)  // G5
#define EXAMPLE_PIN_NUM_DATA11   (46)  // R0
#define EXAMPLE_PIN_NUM_DATA12   (3)   // R1
#define EXAMPLE_PIN_NUM_DATA13   (8)   // R2
#define EXAMPLE_PIN_NUM_DATA14   (18)  // R3
#define EXAMPLE_PIN_NUM_DATA15   (17)   // R4

#define EXAMPLE_PIN_NUM_DISP_EN        (-1)
#define EXAMPLE_PIN_NUM_RST            (-1) // LCD RESET

#define EXAMPLE_LCD_H_RES              480
#define EXAMPLE_LCD_V_RES              480

#define EXAMPLE_I2C_NUM                 (0)   // I2C number
#define EXAMPLE_I2C_SCL                 15
#define EXAMPLE_I2C_SDA                 16

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2

SemaphoreHandle_t sem_vsync_end;
SemaphoreHandle_t sem_gui_ready;

static void example_lvgl_touch_cb(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    /* Read touch controller data */
    esp_lcd_touch_read_data(drv->user_data);

    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(drv->user_data, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    // 防止按住屏幕时不停重置定时器
    static bool is_touching = false;

    if (touchpad_pressed && touchpad_cnt > 0) {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PR;
        // ESP_LOGI(TAG, "X=%u Y=%u", data->point.x, data->point.y);

        if (!is_touching) {
            reset_idle_monitor();
            is_touching = true;
        }
    } else {
        data->state = LV_INDEV_STATE_REL;
        is_touching = false;
    }
}

static bool example_on_vsync_event(esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *event_data, void *user_data)
{
    BaseType_t high_task_awoken = pdFALSE;
    // if (xSemaphoreTakeFromISR(sem_gui_ready, &high_task_awoken) == pdTRUE) {
    //     xSemaphoreGiveFromISR(sem_vsync_end, &high_task_awoken);
    // }
    return high_task_awoken == pdTRUE;
}

static void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
	esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
	// xSemaphoreGive(sem_gui_ready);
	// xSemaphoreTake(sem_vsync_end, portMAX_DELAY);
    // ESP_LOGI("FLUSH", "刷图区域: (%d,%d)-(%d,%d)", area->x1, area->y1, area->x2, area->y2);
	esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
	lv_disp_flush_ready(drv);
}

static void example_increase_lvgl_tick(void *arg)
{
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}
SemaphoreHandle_t xGuiSemaphore;


void lvgl_task(void *pvParameter)
{
    static lv_disp_draw_buf_t disp_buf;
    static lv_disp_drv_t disp_drv;

    (void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    ESP_LOGI(TAG, "Create semaphores");
    sem_vsync_end = xSemaphoreCreateBinary();
    assert(sem_vsync_end);
    sem_gui_ready = xSemaphoreCreateBinary();
    assert(sem_gui_ready);

    ESP_LOGI(TAG, "Turn off LCD backlight");

    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_BK_LIGHT
    };
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

    st7701s_init();

    ESP_LOGI(TAG, "Install RGB LCD panel driver");
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_rgb_panel_config_t panel_config = {
        .data_width = 16, // RGB565 in parallel mode, thus 16bit in width
        .psram_trans_align = 64,
        .bounce_buffer_size_px = 10 * EXAMPLE_LCD_H_RES,
        .clk_src = LCD_CLK_SRC_PLL240M,
        .disp_gpio_num = EXAMPLE_PIN_NUM_DISP_EN,
        .pclk_gpio_num = EXAMPLE_PIN_NUM_PCLK,
        .vsync_gpio_num = EXAMPLE_PIN_NUM_VSYNC,
        .hsync_gpio_num = EXAMPLE_PIN_NUM_HSYNC,
        .de_gpio_num = EXAMPLE_PIN_NUM_DE,
        .data_gpio_nums = {
            EXAMPLE_PIN_NUM_DATA0,
            EXAMPLE_PIN_NUM_DATA1,
            EXAMPLE_PIN_NUM_DATA2,
            EXAMPLE_PIN_NUM_DATA3,
            EXAMPLE_PIN_NUM_DATA4,
            EXAMPLE_PIN_NUM_DATA5,
            EXAMPLE_PIN_NUM_DATA6,
            EXAMPLE_PIN_NUM_DATA7,
            EXAMPLE_PIN_NUM_DATA8,
            EXAMPLE_PIN_NUM_DATA9,
            EXAMPLE_PIN_NUM_DATA10,
            EXAMPLE_PIN_NUM_DATA11,
            EXAMPLE_PIN_NUM_DATA12,
            EXAMPLE_PIN_NUM_DATA13,
            EXAMPLE_PIN_NUM_DATA14,
            EXAMPLE_PIN_NUM_DATA15,
        },
        .timings = {
            .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
            .h_res = EXAMPLE_LCD_H_RES,
            .v_res = EXAMPLE_LCD_V_RES,
            .hsync_back_porch = 1,
            .hsync_front_porch = 4,
            .hsync_pulse_width = 1,
            .vsync_back_porch = 10,
            .vsync_front_porch = 10,
            .vsync_pulse_width = 2,

            .flags.pclk_active_neg = false,
        },
        .flags.fb_in_psram = true, // allocate frame buffer in PSRAM
    };
    ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &panel_handle));
    ESP_LOGI(TAG, "Register event callbacks");
    esp_lcd_rgb_panel_event_callbacks_t cbs = {
        .on_vsync = example_on_vsync_event,
    };
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_register_event_callbacks(panel_handle, &cbs, &disp_drv));

    ESP_LOGI(TAG, "Initialize RGB LCD panel");
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

    esp_lcd_touch_handle_t tp = NULL;
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;

    ESP_LOGI(TAG, "Initialize I2C");

    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = EXAMPLE_I2C_SDA,
        .scl_io_num = EXAMPLE_I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };
    /* Initialize I2C */
    ESP_ERROR_CHECK(i2c_param_config(EXAMPLE_I2C_NUM, &i2c_conf));
    ESP_ERROR_CHECK(i2c_driver_install(EXAMPLE_I2C_NUM, i2c_conf.mode, 0, 0, 0));

    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    

    ESP_LOGI(TAG, "Initialize touch IO (I2C)");
    /* Touch IO handle */
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)EXAMPLE_I2C_NUM, &tp_io_config, &tp_io_handle));
    esp_lcd_touch_config_t tp_cfg = {
        .x_max = EXAMPLE_LCD_V_RES,
        .y_max = EXAMPLE_LCD_H_RES,
        .rst_gpio_num = -1,
        .int_gpio_num = -1,
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    /* Initialize touch */
    ESP_LOGI(TAG, "Initialize touch controller GT911");
    if(esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp) != ESP_OK) {
        ESP_ERROR_CHECK(esp_lcd_panel_io_del(tp_io_handle));

        if (tp_io_config.dev_addr == 0x5D) {
            tp_io_config.dev_addr = 0x14;
        } else if (tp_io_config.dev_addr == 0x14) {
            tp_io_config.dev_addr = 0x5D;
        } else {
            ESP_LOGE(TAG, "tp_io_config.dev_addr: %ld", tp_io_config.dev_addr);
        }
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)EXAMPLE_I2C_NUM, &tp_io_config, &tp_io_handle));
        
        esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp);
    }

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();

    void *buf1 = NULL;
    void *buf2 = NULL;
    ESP_LOGI(TAG, "Allocate separate LVGL draw buffers from PSRAM");
    //缓存视实际项目使用MALLOC_CAP_SPIRAM或MALLOC_CAP_DMA
    //优先使用内部MALLOC_CAP_DMA 刷屏会提高一个档次
    //优先使用双buffer

    buf1 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 480 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);//MALLOC_CAP_SPIRAM
    assert(buf1);
    buf2 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 480 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);//MALLOC_CAP_DMA
    assert(buf2);

    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, EXAMPLE_LCD_H_RES * 480);


    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = example_lvgl_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    lv_disp_t *disp=lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;    // Input device driver (Touch)
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.disp = disp;
    indev_drv.read_cb = example_lvgl_touch_cb;
    indev_drv.user_data = tp;

    indev_touch = lv_indev_drv_register(&indev_drv);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &example_increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000));

    ui_init();

	while (1)
	{
		if (xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            uint32_t delay = lv_timer_handler();
            ui_tick();
            xSemaphoreGive(xGuiSemaphore);
            vTaskDelay(pdMS_TO_TICKS(delay > 10 ? 10 : delay)); // 限制最大delay防止UI过顿
        }
	}
}