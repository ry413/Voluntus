#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_netif.h>
#include "ui.h"
#include "rs485.h"
#include "air.h"
#include "wifi.h"
#include "idle_manager.h"

#define TAG "main.cpp"

extern "C" void lvgl_task(void *pvParameter);

static void monitor_task(void *pvParameter) {
	while(1) {
        printf("free INTERNAL: %d, DMA: %d\n",
                heap_caps_get_free_size(MALLOC_CAP_INTERNAL), heap_caps_get_free_size(MALLOC_CAP_DMA));
		vTaskDelay(60000 / portTICK_PERIOD_MS);
	}
}

extern "C" void app_main(void) {
    esp_err_t err;

    ESP_LOGI(TAG, "Initializing...");

    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
        err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_LOGI(TAG, "NVS 初始化成功");

    xTaskCreatePinnedToCore(lvgl_task, "lvgl_task", 4096 * 2, nullptr, 10, nullptr, 1);
    xTaskCreate(monitor_task, "monitor_task", 3072, nullptr, 1, nullptr);
    rs485_init();
    init_air_commit_timer();    // 空调防抖定时器

    // esp_netif_init();
    // start_wifi_network();
}
