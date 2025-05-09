#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "backlight.h"
#include "actions.h"
#include "screens.h"

#define TAG "BACKLIGHT"

void init_backlight() {
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_RESOLUTION,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 20000,
        .clk_cfg = LEDC_USE_APB_CLK
    };
    ledc_channel_config_t ledc_conf = {
        .gpio_num = LEDC_PIN,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = MAX_BACKLIGHT_DUTY,
        .hpoint = 0
    };
    ledc_timer_config(&timer_conf);
    ledc_channel_config(&ledc_conf);
}

void open_backlight() {
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, MAX_BACKLIGHT_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void close_backlight() {
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

// 点击待机界面的任何地方, 醒来. 也会被语音指令调用, 我知道这好像非常耦合
extern "C" void action_click_wakeup(lv_event_t *e) {
    if (lv_obj_has_flag(objects.idle_overlay, LV_OBJ_FLAG_HIDDEN)) {
        open_backlight();
    } else {
        lv_obj_add_flag(objects.idle_overlay, LV_OBJ_FLAG_HIDDEN);
        // 等隐藏完这个了再打开背光
        xTaskCreate([](void *param) {
            vTaskDelay(pdMS_TO_TICKS(300));
            open_backlight();
            vTaskDelete(nullptr);
        }, "wait_open_backlight", 1024, nullptr, 5, nullptr);
    }
}

// 点击待机界面的熄屏按钮
extern "C" void action_turn_off_backlight(lv_event_t *e) {
    // 因为就算关闭背光了, 这个按钮还是在原地, 所以当背光duty为0时触发就当成误触, 实际上用户应该是想唤醒
    if (ledc_get_duty(LEDC_MODE, LEDC_CHANNEL) == 0) {
        action_click_wakeup(e);
    }
    // 通常就都是关背光
    else {
        close_backlight();
    }
}
