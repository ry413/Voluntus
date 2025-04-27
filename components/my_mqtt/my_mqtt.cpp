#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "mqtt_client.h"
#include "esp_mac.h"
#include "esp_timer.h"
#include "esp_ota_ops.h"
#include "esp_https_ota.h"
#include "esp_crt_bundle.h"

#include "../json.hpp"

#include "my_mqtt.h"

static const char *TAG = "mqtt";
using json = nlohmann::json;

esp_mqtt_client_handle_t client;

char full_topic[40];

static std::string g_ota_url;

void static read_room_info_from_nvs(std::string &hotel_name, std::string &room_name);
static void handle_mqtt_ndjson(const char* data, size_t data_len);
void ota_task(void *param) {
    ESP_LOGI(TAG, "Starting OTA task, URL=%s", g_ota_url.c_str());

    esp_http_client_config_t http_config = {};
    http_config.url = g_ota_url.c_str();
    http_config.crt_bundle_attach = esp_crt_bundle_attach; 
    http_config.event_handler = nullptr;
    http_config.keep_alive_enable = true;
    http_config.use_global_ca_store = true;
    http_config.skip_cert_common_name_check = true;

    esp_https_ota_config_t ota_config = {};
    ota_config.http_config = &http_config;

    char buffer[128];
    snprintf(buffer, sizeof(buffer), "试图OTA: %s", g_ota_url.c_str());
    ESP_LOGI("ota", "%s", buffer);
    
    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        snprintf(buffer, sizeof(buffer), "OTA完成, 准备重启");
        ESP_LOGI(TAG, "%s", buffer);
        vTaskDelay(pdMS_TO_TICKS(2000));
        esp_restart();
    } else {
        snprintf(buffer, sizeof(buffer), "OTA upgrade failed: %s", esp_err_to_name(ret));
        ESP_LOGE(TAG, "%s", buffer);
    }
    vTaskDelete(NULL);
}

void start_ota_upgrade(const std::string &url) {
    g_ota_url = url;
    xTaskCreatePinnedToCore(ota_task, "ota_task", 8192, nullptr, 5, nullptr, 1);
}

// 固定间隔上报所有设备状态
static void report_state_task(void *param) {
    while (true) {
        report_states();

        vTaskDelay(60000 / portTICK_PERIOD_MS);

        UBaseType_t remaining_stack = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI(__func__, "Remaining stack size: %u", remaining_stack);
    }
    vTaskDelete(nullptr);
}

// 固定间隔上报过去一分钟的操作记录
// static void report_operation_task(void *param) {
//     while (true) {
//         report_op_logs();

//         vTaskDelay(60000 / portTICK_PERIOD_MS);
//     }
//     vTaskDelete(nullptr);
// }
// static void register_the_rcu();
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    client = event->client;
    
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
    {
            esp_mqtt_client_subscribe(client, full_topic, 0);
            printf("已订阅接收主题: %s\n", full_topic);

            // 注册本机
            // register_the_rcu();
            // // 启动报告状态任务
            // static TaskHandle_t report_st_task_handle;
            // if (report_st_task_handle == nullptr) {
            //     xTaskCreate(report_state_task, "report_state_task", 4096, nullptr, 3, &report_st_task_handle);
            // }
            // 启动报告操作任务
            // static TaskHandle_t report_op_task_handle;
            // if (report_op_task_handle == nullptr) {
            //     xTaskCreate(report_operation_task, "report_operation_task", 8192, nullptr, 3, &report_op_task_handle);
            // }

            // 广播时间
            // time_t now = get_current_timestamp();

            // if (now != 0) {
            //     uint8_t p2, p3, p4, p5;
            //     p2 = (now >> 24) & 0xFF;
            //     p3 = (now >> 16) & 0xFF;
            //     p4 = (now >> 8)  & 0xFF;
            //     p5 = now & 0xFF;
                
            //     generate_response(ALL_TIME_SYNC, p2, p3, p4, p5);
            // }

            break;
    }

    case MQTT_EVENT_DATA:
    {
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        ESP_LOGI(TAG, "DATA=%.*s\r\n", event->data_len, event->data);
        std::string msg_data(event->data, event->data_len);
        // handle_mqtt_ndjson(msg_data.c_str(), msg_data.size());
        break;
    }
    default:
        break;
    }
}
void mqtt_app_start() {
    if (client) {
        ESP_LOGW(TAG, "MQTT client 非预期存在, 自动清理旧连接");
        mqtt_app_stop();
    }
    
    // if (std::string(get_serial_num()).empty()) {
    //     ESP_LOGW(TAG, "此设备无序列号, 停止连接mqtt");
    //     return;
    // }
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {.address = {.uri = "mqtt://xiaozhuiot.cn:1883",}},
        .credentials = {
            .username = "xiaozhu",
            .authentication = {.password = "ieTOIugSDfieWw23gfiwefg"},
        },
        .session = {.protocol_ver = MQTT_PROTOCOL_V_5},
        .task = {.stack_size = 8192},
        .buffer = {.size = 20480},
    };

    // snprintf(full_topic, sizeof(full_topic), "/XZRCU/DOWN/%s", get_serial_num());

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}
void mqtt_app_stop(void) {
    if (client) {
        esp_mqtt_client_stop(client);
        esp_mqtt_client_destroy(client);
        client = NULL;
        ESP_LOGI(TAG, "MQTT 已停止");
    }
}

void mqtt_publish_message(const std::string& message, int qos, int retain) {
    // if (!client || !network_is_ready()) {
    //     return;
    // }
    char up_topic[40];
    // snprintf(up_topic, sizeof(up_topic), "/XZRCU/UP/%s", get_serial_num());
    // int msg_id = esp_mqtt_client_publish(client, up_topic, message.c_str(), message.length(), qos, retain);
    // ESP_LOGI(TAG, "Message sent, msg_id=%d, topic=%s, message=%s", msg_id, up_topic, message.c_str());
}

// // 注册时携带所有信息
// static void register_the_rcu() {
//     nlohmann::json j;
//     j["mac"] = get_serial_num();
//     j["type"] = "regis";

//     auto& config_version = LordManager::getInstance().getConfigVersion();
//     j["config_version"] = config_version;

//     // 从 NVS 中读取房间信息
//     std::string hotel_name, room_name;
//     read_room_info_from_nvs(hotel_name, room_name);

//     j["hotel_name"] = hotel_name;
//     j["room_name"] = room_name;

//     int64_t uptime_us = esp_timer_get_time();
//     int64_t uptime_s = uptime_us / 1000000;
//     j["run_time"] = uptime_s;

//     j["fireware_version"] = AETHORAC_VERSION;

//     j["model_name"] = MODEL_NAME;

//     // 构造 lights
//     j["lights"] = nlohmann::json::array();
//     auto lamps = DeviceManager::getInstance().getDevicesOfType<Lamp>();
//     for (auto& lamp : lamps) {
//         nlohmann::json lamp_obj;
//         lamp_obj["id"] = std::to_string(lamp->uid);
//         lamp_obj["name"] = lamp->name;
//         lamp_obj["output_type"] = std::to_string(static_cast<int>(lamp->output->type));
//         lamp_obj["output_num"] = std::to_string(lamp->output->channel);
//         lamp_obj["state"] = lamp->isOn() ? "1" : "0";
//         // 此灯可能存在的关联灯
//         if (!lamp->link_device_uids.empty()) {
//             lamp_obj["union_light_ids"] = nlohmann::json::array();
//             for (auto uid : lamp->link_device_uids) {
//                 lamp_obj["union_light_ids"].push_back(std::to_string(uid));
//             }
//         }
        
//         j["lights"].push_back(lamp_obj);
//     }

//     // 构造 curtains
//     j["curtains"] = nlohmann::json::array();
//     auto curtains = DeviceManager::getInstance().getDevicesOfType<Curtain>();
//     for (auto& curtain : curtains) {
//         nlohmann::json curtain_obj;
//         curtain_obj["id"] = std::to_string(curtain->uid);
//         curtain_obj["name"] = curtain->name;
//         curtain_obj["output_open_type"] = std::to_string(static_cast<int>(curtain->output_open->type));
//         curtain_obj["output_open_num"] = std::to_string(curtain->output_open->channel);
//         curtain_obj["output_close_type"] = std::to_string(static_cast<int>(curtain->output_close->type));
//         curtain_obj["output_close_num"] = std::to_string(curtain->output_close->channel);
//         curtain_obj["state"] = curtain->getState() ? "1" : "0";
//         j["curtains"].push_back(curtain_obj);
//     }

//     // 构造 other(device)
//     j["others"] = nlohmann::json::array();
//     auto others = DeviceManager::getInstance().getDevicesOfType<OtherDevice>();
//     for (auto& other : others) {
//         if (other->type == OtherDeviceType::OUTPUT_CONTROL) {
//             nlohmann::json other_obj;
//             other_obj["id"] = std::to_string(other->uid);
//             other_obj["name"] = other->name;
//             other_obj["output_type"] = std::to_string(static_cast<int>(other->output->type));
//             other_obj["output_num"] = std::to_string(other->output->channel);
//             other_obj["state"] = other->isOn() ? "1" : "0";
//             j["others"].push_back(other_obj);
//         }
//     }

//     // 构造 airCon
//     j["airs"] = nlohmann::json::array();
//     auto airs = DeviceManager::getInstance().getDevicesOfType<AirConBase>();
//     for (auto& air : airs) {
//         nlohmann::json air_item;
//         air_item["id"] = std::to_string(air->uid);
//         air_item["air_id"] = std::to_string(air->ac_id);
//         air_item["name"] = air->name;
//         air_item["type"] = std::to_string(static_cast<int>(air->ac_type));
//         air_item["state"] = air->get_state() ? "1" : "0";
//         air_item["mode"] = std::to_string(static_cast<int>(air->get_mode()));
//         air_item["fan_speed"] = std::to_string(static_cast<int>(air->get_fan_speed()));
//         air_item["target_temp"] = std::to_string(air->get_target_temp());
//         if (air->ac_type != ACType::INFRARED) {
//             std::shared_ptr<SinglePipeFCU> single_pipe_ac = std::dynamic_pointer_cast<SinglePipeFCU>(air);
//             air_item["low_output_type"] = std::to_string(static_cast<int>(single_pipe_ac->low_output->type));
//             air_item["low_output_num"] = std::to_string(single_pipe_ac->low_output->channel);
//             air_item["mid_output_type"] = std::to_string(static_cast<int>(single_pipe_ac->mid_output->type));
//             air_item["mid_output_num"] = std::to_string(single_pipe_ac->mid_output->channel);
//             air_item["high_output_type"] = std::to_string(static_cast<int>(single_pipe_ac->high_output->type));
//             air_item["high_output_num"] = std::to_string(single_pipe_ac->high_output->channel);
//             air_item["water_output_type"] = std::to_string(static_cast<int>(single_pipe_ac->water1_output->type));
//             air_item["water_output_num"] = std::to_string(single_pipe_ac->water1_output->channel);
//         } else {
//             std::shared_ptr<InfraredAC> infrared_ac = std::dynamic_pointer_cast<InfraredAC>(air);
//             air_item["code_base"] = infrared_ac->get_code_base();
//         }

//         j["airs"].push_back(air_item);
//     }

//     // 构造 modes
//     // panel没找到的话就在input里找到
//     j["modes"] = nlohmann::json::array();
//     auto& panels = PanelManager::getInstance().getAllItems();
//     for (auto& [_, panel] : panels) {
//         for (auto& [_, button] : panel->buttons) {
//             if (!button->mode_name.empty()) {
//                 j["modes"].push_back(button->mode_name);
//             }
//         }
//     }
//     auto& boards = BoardManager::getInstance().getAllItems();
//     for (auto& [_, board] : boards) {
//         for (auto& input : board->inputs) {
//             if (!input.mode_name.empty()) {
//                 j["modes"].push_back(input.mode_name);
//             }
//         }
//     }


//     std::string json_str = j.dump();
//     mqtt_publish_message(json_str.c_str(), 0, 0);
// }

// void report_states() {
//     // if (!ethernet_is_ready()) {
//     //     return;
//     // }
    
//     print_free_memory("准备上报状态");
    
//     nlohmann::json j;
//     j["mac"] = get_serial_num();
//     j["type"] = "alldevicestate";

//     auto lamps = DeviceManager::getInstance().getDevicesOfType<Lamp>();
//     j["lights"] = nlohmann::json::array();
//     j["lights"].get_ref<nlohmann::json::array_t&>().reserve(lamps.size());
//     for (auto& lamp : lamps) {
//         nlohmann::json lamp_obj;
//         lamp_obj["id"] = lamp->uid;
//         lamp_obj["state"] = lamp->isOn() ? 1 : 0;
//         j["lights"].push_back(lamp_obj);
//     }

//     auto curtains = DeviceManager::getInstance().getDevicesOfType<Curtain>();
//     j["curtains"] = nlohmann::json::array();
//     j["curtains"].get_ref<nlohmann::json::array_t&>().reserve(curtains.size());
//     for (auto& curtain : curtains) {
//         nlohmann::json curtain_obj;
//         curtain_obj["id"] = curtain->uid;
//         curtain_obj["state"] = curtain->getState() ? 1 : 0;
//         j["curtains"].push_back(curtain_obj);
//     }

//     auto others = DeviceManager::getInstance().getDevicesOfType<OtherDevice>();
//     size_t othersCount = 0;
//     for (auto& other : others) {
//         if (other->type == OtherDeviceType::OUTPUT_CONTROL) {
//             ++othersCount;
//         }
//     }
//     j["others"] = nlohmann::json::array();
//     j["others"].get_ref<nlohmann::json::array_t&>().reserve(othersCount);
//     for (auto& other : others) {
//         if (other->type == OtherDeviceType::OUTPUT_CONTROL) {
//             nlohmann::json other_obj;
//             other_obj["id"] = other->uid;
//             other_obj["state"] = other->isOn() ? 1 : 0;
//             j["others"].push_back(other_obj);
//         }
//     }

//     auto airs = DeviceManager::getInstance().getDevicesOfType<AirConBase>();
//     j["airs"] = nlohmann::json::array();
//     j["airs"].get_ref<nlohmann::json::array_t&>().reserve(airs.size());
//     for (auto& air : airs) {
//         nlohmann::json air_item;
//         air_item["id"] = air->uid;
//         air_item["state"] = air->get_state() ? 1 : 0;
//         air_item["mode"] = static_cast<int>(air->get_mode());
//         air_item["fan_speed"] = static_cast<int>(air->get_fan_speed());
//         air_item["target_temp"] = air->get_target_temp();
//         air_item["room_temp"] = air->get_room_temp();
//         j["airs"].push_back(air_item);
//     }

//     // 模式
//     j["mode"] = LordManager::getInstance().getCurrMode();
//     // 状态
//     j["states"] = get_states();

//     print_free_memory("准备j.dump()");
//     std::string json_str = j.dump();
//     mqtt_publish_message(json_str.c_str(), 0, 0);
// }

// static void handle_mqtt_ndjson(const char* data, size_t data_len) {
//     auto lines = splitByLine(data);

//     if (lines.empty()) {
//         ESP_LOGW(TAG, "接收到空行，忽略");
//         return;
//     }

//     json obj;
//     try {
//         obj = json::parse(lines[0]);
//     } catch (const std::exception& e) {
//         ESP_LOGW(TAG, "JSON 解析失败: %s", e.what());
//         return;
//     }

//     if (obj.empty()) {
//         ESP_LOGW(TAG, "解析后的 JSON 是空的");
//         return;
//     }

//     auto it = obj.begin();
//     const std::string& key = it.key();
//     const json& value = it.value();

//     std::string type = value.get<std::string>();
//     printf("key: %s, value: %s\n", key.c_str(), type.c_str());
//     if (key == "type") {
//         if (type == "urge") {
//             report_states();
//             return;
//         } else if (type == "oracle") {
//             auto msg = json::parse(lines[1]);
//             if (msg.is_object()) {
//                 if (msg.contains("operation") && msg["operation"].is_string()) {
//                     std::string operation = msg["operation"].get<std::string>();
//                     // 查stm32版本号
//                     if (operation == "stm32_version") {
//                         uart_frame_t frame;
//                         build_frame(0xFF, 00, 00, 00, 00, &frame);
//                         send_frame(&frame);
//                     }
//                     // 指定继电器进入测试模式
//                     else if (operation == "stm32_test") {
//                         if (msg.contains("target") && msg["target"].is_string()
//                         && msg.contains("state") && msg["state"].is_string()) {
//                             std::string target = msg["target"].get<std::string>();
//                             std::string state = msg["state"].get<std::string>();

//                             uart_frame_t frame;
//                             build_frame(0x07, std::stoi(target), std::stoi(state), 00, 00, &frame);
//                             send_frame(&frame);
//                         }
//                     }
//                 }
//             }
//             return;
//         } else if (type == "ota") {
//             auto msg = json::parse(lines[1]);
//             if (msg.is_object()) {
//                 if (msg.contains("ver") && msg["ver"].is_string() &&
//                     msg.contains("url") && msg["url"].is_string()) {
//                     const std::string ver = msg["ver"].get<std::string>();
//                     const std::string ota_url = msg["url"].get<std::string>();
//                     if (ver != AETHORAC_VERSION) {
//                         ESP_LOGI(TAG, "OTA: %s -> %s", AETHORAC_VERSION, ver.c_str());
//                         start_ota_upgrade(ota_url);
//                     } else {
//                         ESP_LOGI(TAG, "Same version, skip OTA.");
//                     }
//                 }
//             }
//             return;
//         } else if (type == "restart") {
//             esp_restart();
//         } else if (type == "GET_FILE") {
//             ESP_LOGI(TAG, "通过MQTT收到 GET_FILE 命令");
//             int file_fd = open(FILE_PATH, O_RDONLY);
//             if (file_fd < 0) {
//                 ESP_LOGE(TAG, "读取文件失败");
//                 std::string error_msg = "ERROR: File not found\n";
//                 mqtt_publish_message(error_msg, 1, 0);
//             } else {
//                 char file_buf[1024];
//                 ssize_t read_bytes;
//                 std::string file_data;
//                 // 分段读取文件内容
//                 while ((read_bytes = read(file_fd, file_buf, sizeof(file_buf))) > 0) {
//                     file_data.append(file_buf, read_bytes);
//                 }
//                 close(file_fd);
//                 // 结束标识
//                 mqtt_publish_message(file_data, 1, 0);
//             }
//             return;
//         } else if (type == "room_info") {
//             auto msg = json::parse(lines[1]);
//             if (msg.is_object()) {
//                 ESP_LOGI(TAG, "收到房间信息数据");
//                 if (msg.contains("hotel_name") && msg["hotel_name"].is_string() &&
//                     msg.contains("room_name") && msg["room_name"].is_string()) {
                    
//                     std::string hotel_name = msg["hotel_name"].get<std::string>();
//                     std::string room_name = msg["room_name"].get<std::string>();

//                     ESP_LOGI(TAG, "hotel_name: %s, room_name: %s", hotel_name.c_str(), room_name.c_str());

//                     nvs_handle_t handle;
//                     esp_err_t err = nvs_open("storage", NVS_READWRITE, &handle);
//                     if (err != ESP_OK) {
//                         ESP_LOGE(TAG, "打开 NVS 句柄失败: %s", esp_err_to_name(err));
//                         return;
//                     }
//                     err = nvs_set_str(handle, "hotel_name", hotel_name.c_str());
//                     if (err != ESP_OK) {
//                         ESP_LOGE(TAG, "写入 hotel_name 失败: %s", esp_err_to_name(err));
//                     }
//                     err = nvs_set_str(handle, "room_name", room_name.c_str());
//                     if (err != ESP_OK) {
//                         ESP_LOGE(TAG, "写入 room_name 失败: %s", esp_err_to_name(err));
//                     }
//                     err = nvs_commit(handle);
//                     if (err != ESP_OK) {
//                         ESP_LOGE(TAG, "提交数据失败: %s", esp_err_to_name(err));
//                     }
//                     nvs_close(handle);
//                 }
//             }
//             return;
//         } else if (type == "wifi_cfg") {
//             auto msg = json::parse(lines[1]);
//             if (msg.is_object()) {
//                 ESP_LOGI(TAG, "通过网络收到WiFi配置");
//                 if (msg.contains("ssid") && msg["ssid"].is_string() &&
//                     msg.contains("pass") && msg["pass"].is_string()) {
//                         save_wifi_credentials(msg["ssid"].get<std::string>().c_str(),
//                                               msg["pass"].get<std::string>().c_str());
//                 }
//             }
//             return;
//         } else if (type == "change_net_type") {
//             auto msg = json::parse(lines[1]);
//             if (msg.is_object()) {
//                 ESP_LOGI(TAG, "通过网络收到更改网络驱动请求");
//                 if (msg.contains("target") && msg["target"].is_string()) {
//                     auto val = msg["target"].get<std::string>();
//                     if (val == "1") {
//                         start_wifi_network();
//                     } else if (val == "2") {
//                         start_ethernet_network();
//                     } else {
//                         ESP_LOGE(TAG, "错误参数: %s", val.c_str());
//                     }
//                 }
//             }
//             return;
//         } else if (type == "Laminor") {
//             ESP_LOGI(TAG, "通过MQTT收到 JSON 配置数据");

//             auto fit_obj = json::parse(lines[1]);

//             auto it = fit_obj.begin();
//             const std::string& key = it.key();
//             const json& value = it.value();

//             std::string fit_version = value.get<std::string>();
//             if (fit_version != FIT_LAMINOR_VERSION) {
//                 ESP_LOGE(TAG, "版本不适配: %s / %s", fit_version.c_str(), FIT_LAMINOR_VERSION);
//                 return;    
//             }

//             char buffer[128];
//             size_t total = 0, used = 0;
//             esp_err_t ret = esp_littlefs_info(LFS_PARTITION_LABEL, &total, &used);
//             if (ret == ESP_OK) {
//                 ESP_LOGI(TAG, "LittleFS 总容量: %d 字节, 已用: %d 字节", total, used);
//             } else {
//                 snprintf(buffer, sizeof(buffer), "获取 LittleFS 信息失败: %s", esp_err_to_name(ret));
//                 ESP_LOGE(TAG, "%s", buffer);
//             }

//             int file_fd = open(FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0666);
//             if (file_fd < 0) {
//                 snprintf(buffer, sizeof(buffer), "打开文件失败: %s", strerror(errno));
//                 ESP_LOGE(TAG, "%s", buffer);
//             } else {
//                 ssize_t bytes_written = write(file_fd, data, data_len);
//                 if (bytes_written < 0) {
//                     snprintf(buffer, sizeof(buffer), "写入文件失败: %s %d", strerror(errno), errno);
//                     ESP_LOGE(TAG, "%s", buffer);
//                 } else {
//                     ESP_LOGI(TAG, "成功保存到文件, 5秒后应用配置");
        
//                     xTaskCreate([](void *param) {
//                         print_free_memory();
//                         vTaskDelay(5000 / portTICK_PERIOD_MS);
//                         print_free_memory();
//                         parseNdJson(read_json_to_string(FILE_PATH));
//                         register_the_rcu();
//                         vTaskDelete(nullptr);
//                     }, "parsejson", 8192, nullptr, 3, nullptr);
//                 }
//                 close(file_fd);
//             }
//             return;
//         } else if (type == "ctl") {
//             // 解析字段 "devicetype"
//             std::string devicetype;
//             auto msg = json::parse(lines[1]);
//             if (msg.is_object()) {
//                 if (msg.contains("devicetype") && msg["devicetype"].is_string()) {
//                     devicetype = msg["devicetype"].get<std::string>();
//                     ESP_LOGI(TAG, "devicetype: %s", devicetype.c_str());
//                 } else {
//                     ESP_LOGW(TAG, "Field 'devicetype' is missing or not a string.");
//                 }
            
//                 // 解析字段 "deviceid"
//                 uint16_t deviceid_u16 = 0;
//                 bool deviceid_valid = false;
//                 if (msg.contains("deviceid") && msg["deviceid"].is_string()) {
//                     std::string deviceid_str = msg["deviceid"].get<std::string>();
//                     ESP_LOGI(TAG, "deviceid: %s", deviceid_str.c_str());
            
//                     int deviceid = std::stoi(deviceid_str);
//                     if (deviceid >= 0 && deviceid <= std::numeric_limits<uint16_t>::max()) {
//                         deviceid_u16 = static_cast<uint16_t>(deviceid);
//                         deviceid_valid = true;
//                     } else {
//                         ESP_LOGE(TAG, "deviceid超出了uint16_t的范围: %d", deviceid);
//                     }
//                 } else {
//                     ESP_LOGW(TAG, "Field 'deviceid' is missing or not a string.");
//                 }
            
//                 // 解析字段 "operation"
//                 std::string operation_str;
//                 if (msg.contains("operation") && msg["operation"].is_string()) {
//                     operation_str = msg["operation"].get<std::string>();
//                     ESP_LOGI(TAG, "operation: %s", operation_str.c_str());
//                 } else {
//                     ESP_LOGW(TAG, "Field 'operation' is missing or not a string.");
//                 }
            
//                 // 解析字段 "param"
//                 std::string param_str;
//                 if (msg.contains("param") && msg["param"].is_string()) {
//                     param_str = msg["param"].get<std::string>();
//                     ESP_LOGI(TAG, "param: %s", param_str.c_str());
//                 } else {
//                     ESP_LOGW(TAG, "Field 'param' is missing or not a string.");
//                 }
            
//                 // 根据解析到的字段值执行操作
//                 if (devicetype == "mode") {
//                     // 切换模式
//                     auto& panels = PanelManager::getInstance().getAllItems();
//                     // 遍历所有面板的按钮, 执行对应的模式按钮
//                     for (auto& [_, panel] : panels) {
//                         for (auto& [_, button] : panel->buttons) {
//                             if (button->mode_name == operation_str) {
//                                 button->execute();
//                                 return;
//                             }
//                         }
//                     }
//                     // 没找到的话就在输入里找
//                     auto& boards = BoardManager::getInstance().getAllItems();
//                     for (auto& [_, board] : boards) {
//                         for (auto& input : board->inputs) {
//                             if (input.mode_name == operation_str) {
//                                 input.execute();
//                                 return;
//                             }
//                         }
//                     }

//                     ESP_LOGE(TAG, "不存在的模式: %s", operation_str.c_str());
//                 } else {
//                     // 设备控制
//                     if (deviceid_valid) {
//                         // 设备控制绝对退出模式
//                         LordManager::getInstance().setCurrMode("");
//                         auto device = DeviceManager::getInstance().getItem(deviceid_u16);
//                         // 如果是操控空调, 特殊处理, 不记录操作日志
//                         if (devicetype == "air") {
//                             std::shared_ptr<AirConBase> air = std::dynamic_pointer_cast<AirConBase>(device);
//                             air->execute_backstage(operation_str.c_str(), param_str);
//                         } else {
//                             device->execute(operation_str.c_str(), param_str);
//                             IndicatorHolder::getInstance().callAllAndClear();
//                         }
//                     }
//                 }
//             }
//             return;
//         } else {
//             ESP_LOGE(TAG, "未知的操作类型: %s", type.c_str());
//             return;
//         }
//     }
// }

// // 从nvs中获取酒店名与房号
// // 如果某项不存在，则赋予默认值
// void static read_room_info_from_nvs(std::string &hotel_name, std::string &room_name) {
//     nvs_handle_t handle;
//     esp_err_t err = nvs_open("storage", NVS_READONLY, &handle);
//     if (err != ESP_OK) {
//         ESP_LOGE(TAG, "打开 NVS 句柄失败: %s", esp_err_to_name(err));
//         // 打开失败时直接赋默认值
//         hotel_name = "defHotel";
//         room_name = "defRoom";
//         return;
//     }

//     size_t required_size = 0;
//     // 读取 hotel_name
//     err = nvs_get_str(handle, "hotel_name", NULL, &required_size);
//     if (err == ESP_OK && required_size > 0) {
//         char *hotel_buf = (char *)malloc(required_size);
//         if (hotel_buf) {
//             err = nvs_get_str(handle, "hotel_name", hotel_buf, &required_size);
//             if (err == ESP_OK) {
//                 hotel_name = std::string(hotel_buf);
//             } else {
//                 ESP_LOGE(TAG, "读取 hotel_name 失败: %s", esp_err_to_name(err));
//                 hotel_name = "DefaultHotelName";
//             }
//             free(hotel_buf);
//         } else {
//             ESP_LOGE(TAG, "分配内存失败");
//             hotel_name = "DefaultHotelName";
//         }
//     } else {
//         ESP_LOGI(TAG, "NVS 中没有找到 hotel_name, 使用默认值");
//         hotel_name = "DefaultHotelName";
//     }

//     // 读取 room_name
//     required_size = 0;
//     err = nvs_get_str(handle, "room_name", NULL, &required_size);
//     if (err == ESP_OK && required_size > 0) {
//         char *room_buf = (char *)malloc(required_size);
//         if (room_buf) {
//             err = nvs_get_str(handle, "room_name", room_buf, &required_size);
//             if (err == ESP_OK) {
//                 room_name = std::string(room_buf);
//             } else {
//                 ESP_LOGE(TAG, "读取 room_name 失败: %s", esp_err_to_name(err));
//                 room_name = "DefaultRoomName";
//             }
//             free(room_buf);
//         } else {
//             ESP_LOGE(TAG, "分配内存失败");
//             room_name = "DefaultRoomName";
//         }
//     } else {
//         ESP_LOGI(TAG, "NVS 中没有找到 room_name, 使用默认值");
//         room_name = "DefaultRoomName";
//     }

//     nvs_close(handle);
// }