#include "esp_err.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_timer.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include <esp_sntp.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "wifi.h"
#include <string>
#include "my_mqtt.h"

#define TAG "WIFI"

#define DEFAULT_WIFI_SSID "xz526"
#define DEFAULT_WIFI_PASS "xz526888"
#define WIFI_CONNECTED_BIT BIT0


static esp_netif_t *netif = nullptr;
static EventGroupHandle_t wifi_event_group;
static bool network_ready = false;
static esp_timer_handle_t reconnect_timer;


static bool load_wifi_credentials(char* ssid_out, char* pass_out) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open("wifi_cfg", NVS_READONLY, &handle);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "无法打开NVS, 使用默认WiFi配置");
        strncpy(ssid_out, DEFAULT_WIFI_SSID, 32);
        strncpy(pass_out, DEFAULT_WIFI_PASS, 64);
        return true;
    }

    size_t ssid_len = 32, pass_len = 64;
    esp_err_t res1 = nvs_get_str(handle, "ssid", ssid_out, &ssid_len);
    esp_err_t res2 = nvs_get_str(handle, "pass", pass_out, &pass_len);
    nvs_close(handle);

    if (res1 != ESP_OK || res2 != ESP_OK) {
        ESP_LOGW(TAG, "NVS无有效WiFi配置, 使用默认WiFi");
        strncpy(ssid_out, DEFAULT_WIFI_SSID, 32);
        strncpy(pass_out, DEFAULT_WIFI_PASS, 64);
        return true;
    }

    return true;
}

bool save_wifi_credentials(const char* ssid, const char* pass) {
    nvs_handle_t handle;
    esp_err_t res1 = ESP_OK;
    esp_err_t res2 = ESP_OK;

    if (nvs_open("wifi_cfg", NVS_READWRITE, &handle) != ESP_OK) {
        ESP_LOGE(TAG, "无法打开NVS写入WiFi配置");
        return false;
    }

    if (ssid) {
        res1 = nvs_set_str(handle, "ssid", ssid);
        if (res1 != ESP_OK) {
            ESP_LOGE(TAG, "写入SSID失败: %d", res1);
        }
    }

    if (pass) {
        res2 = nvs_set_str(handle, "pass", pass);
        if (res2 != ESP_OK) {
            ESP_LOGE(TAG, "写入密码失败: %d", res2);
        }
    }

    nvs_commit(handle);
    nvs_close(handle);

    if ((ssid && res1 != ESP_OK) || (pass && res2 != ESP_OK)) {
        return false;
    }

    ESP_LOGI(TAG, "WiFi配置保存成功: SSID=\"%s\" Password=%s",
             ssid ? ssid : "(未更新)", pass ? pass : "(未更新)");
    return true;
}

void reconnect_cb(void* arg) {
    ESP_LOGI(TAG, "定时器触发，尝试 WiFi 重连");
    esp_wifi_connect();
}

void init_reconnect_timer() {
    esp_timer_create_args_t timer_args = {
        .callback = &reconnect_cb,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "wifi_reconnect"
    };
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &reconnect_timer));
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    ESP_LOGI(TAG, "WiFi Event: base=%s, id=%ld", event_base, event_id);
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        network_ready = false;
        mqtt_app_stop();

        if (!esp_timer_is_active(reconnect_timer)) {
            ESP_LOGW(TAG, "WIFI掉线, 5秒后重连");
            esp_timer_start_once(reconnect_timer, 5000000);
        }
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "WiFi got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        // set_ip_raw(event->ip_info.ip.addr);
        // init_sntp_once();
        mqtt_app_start();
        network_ready = true;

        if (esp_timer_is_active(reconnect_timer)) {
            esp_timer_stop(reconnect_timer);
        }
    }
}

static void cleanup_all_network_resources() {
    ESP_LOGI(TAG, "开始清理所有网络资源...");

    // 停止 MQTT（如有）
    mqtt_app_stop();

    // ===== WiFi 清理部分 =====
    esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler);
    esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler);

    esp_wifi_disconnect();
    vTaskDelay(pdMS_TO_TICKS(2000));
    esp_wifi_stop();
    esp_wifi_deinit();

    if (wifi_event_group) {
        vEventGroupDelete(wifi_event_group);
        wifi_event_group = nullptr;
    }

    // ===== 通用 netif 清理 =====
    if (netif) {
        esp_wifi_clear_default_wifi_driver_and_handlers(netif);
        esp_netif_destroy(netif);
        netif = nullptr;
    }

    esp_event_loop_delete_default();

    network_ready = false;

    ESP_LOGI(TAG, "网络资源清理完毕。");
}

void start_wifi_network() {
    cleanup_all_network_resources();

    char ssid[33] = {};
    char pass[65] = {};
    if (!load_wifi_credentials(ssid, pass)) {
        ESP_LOGE(TAG, "无有效WiFi配置, 无法连接");
        return;
    }

    ESP_LOGI(TAG, "试图连接WiFi ssid: %s, pass: %s", ssid, pass);
    
    esp_event_loop_create_default();

    wifi_event_group = xEventGroupCreate();
    ESP_LOGI(TAG, "Creating WiFi netif...");
    netif = esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, nullptr);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, nullptr);

    wifi_config_t wifi_config = {};
    snprintf((char*)wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid), "%s", ssid);
    snprintf((char*)wifi_config.sta.password, sizeof(wifi_config.sta.password), "%s", pass);

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    init_reconnect_timer();
    
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT,
            true, true, pdMS_TO_TICKS(10000));

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "WiFi连接成功.");
    } else {
        ESP_LOGE(TAG, "WiFi连接超时, 释放资源");
        cleanup_all_network_resources();
    }
}

bool network_is_ready() {
    return network_ready;
}