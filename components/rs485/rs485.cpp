#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include "freertos/timers.h"
#include <freertos/task.h>
#include "rs485.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "string.h"
#include "button_control.h"
#include "vars.h"
#include "air.h"
#include <ctime>
#include "ui.h"
#include "screens.h"
#include "time_sync.h"
#include "idle_manager.h"
#include <unordered_map>
#include "actions.h"

static const char *TAG = "RS485";

static QueueHandle_t rs485Queue = nullptr;
static SemaphoreHandle_t rs485_handle_semaphore = nullptr;
static void handle_rs485_data(uint8_t* data, int length);

TimerHandle_t heartbeat_timeout_timer = nullptr;
void heartbeat_timeout_cb(TimerHandle_t xTimer);

// 离线语音相关
static const std::unordered_map<uint32_t, std::string> voice_response = {
    {0x100D0064, "好的, 打开卫浴灯"},
    {0x100D0000, "好的, 关闭卫浴灯"},

    {0x100E0064, "好的, 打开排风扇"},
    {0X100E0000, "好的, 关闭排风扇"},

    {0X100F0064, "好的, 打开镜前灯"},
    {0X100F0000, "好的, 关闭镜前灯"},

    {0X10060064, "好的, 打开灯带"},
    {0X10060000, "好的, 关闭灯带"},
    
    {0X10070064, "好的, 打开廊灯"},
    {0X10070000, "好的, 关闭廊灯"},
    
    {0X10080064, "好的, 打开房灯"},
    {0X10080000, "好的, 关闭房灯"},

    {0X10090064, "好的, 打开壁灯"},
    {0X10090000, "好的, 关闭壁灯"},

    {0X100A0064, "好的, 打开筒灯"},
    {0X100A0000, "好的, 关闭筒灯"},

    {0X100B0064, "好的, 打开射灯"},
    {0X100B0000, "好的, 关闭射灯"},

    {0X100C0064, "好的, 打开床头灯"},
    {0X100C0000, "好的, 关闭床头灯"},

    {0X10120064, "好的, 打开阳台灯"},
    {0X10120000, "好的, 关闭阳台灯"},

    {0X10190064, "好的, 打开阅读灯"},
    {0X10190000, "好的, 关闭阅读灯"},

    {0X10FF0231, "好的, 灯光调暗"},
    {0X10FF0206, "好的, 调到最暗"},
    {0X10FF0207, "好的, 亮度二十"},
    {0X10FF0208, "好的, 亮度三十"},
    {0X10FF0209, "好的, 亮度四十"},
    {0X10FF020A, "好的, 亮度五十"},
    {0X10FF020B, "好的, 亮度六十"},
    {0X10FF020C, "好的, 亮度七十"},
    {0X10FF020D, "好的, 亮度八十"},
    {0X10FF020E, "好的, 亮度九十"},
    {0X10FF020F, "好的, 调到最亮"},
    {0X10FF0301, "好的, 打开调色"},
    {0X10FF0300, "好的, 关闭调色"},
    {0X10FF0302, "好的, 调成红色"},
    {0X10FF0303, "好的, 调成橙色"},
    {0X10FF0304, "好的, 调成黄色"},
    {0X10FF0305, "好的, 调成绿色"},
    {0X10FF0306, "好的, 调成蓝色"}, // ?
    {0X10FF0307, "好的, 调成粉色"},
    {0X10FF0308, "好的, 调成紫色"},

    {0X1E000100, "好的, 打开灯光"},
    {0x1E010100, "好的, 明亮模式"},
    {0x1E010200, "好的, 柔和模式"},
    {0x1E010300, "好的, 会客模式"},
    {0x1E010400, "好的, 阅读模式"},
    {0x1E010500, "好的, 休闲模式"},
    // {0x1E010600} // ?
    {0x1E010700, "好的, 影音模式"},
    {0x1E010800, "好的, 浪漫模式"},
    {0x1E010900, "好的, 温馨模式"},
    {0x1E010A00, "好的, 睡眠模式"},
    {0x1E010B00, "好的, 总关模式"},
    {0x1E010C00, "好的, 总控模式"},
    
    {0x16000100, "好的, 打开空调"},
    {0x16000000, "好的, 关闭空调"},
    {0x16000200, "好的, 制冷模式"},
    {0x16000300, "好的, 制热模式"},
    {0x16000400, "好的, 调到高风"},
    {0x16000500, "好的, 调到中风"},
    {0x16000600, "好的, 调到低风"},
    {0x16000700, "好的, 风速调高"},
    {0x16000800, "好的, 风速调低"},
    {0x16000900, "好的, 温度加"},
    {0x16000A00, "好的, 温度减"},
    
    {0x16010100, "好的, 二十一度"},
    {0x16010200, "好的, 二十二度"},
    {0x16010300, "好的, 二十三度"},
    {0x16010400, "好的, 二三四度"},
    {0x16010500, "好的, 二十五度"},
    {0x16010600, "好的, 二十六度"},
    {0x16010700, "好的, 二十七度"},
    {0x16010800, "好的, 二十八度"},
    {0x16010B00, "好的, 调到最低十八度"},   // ?
    {0x16010C00, "好的, 十九度"},
    {0x16010D00, "好的, 二十度"},
    
    {0x14000200, "好的, 打开窗帘"},
    {0x14000000, "好的, 关闭窗帘"},
    {0x14000100, "好的, 窗帘停止"},
    {0x14010200, "好的, 打开窗纱"},
    {0x14010000, "好的, 关闭窗纱"},
    {0x14010100, "好的, 窗纱停止"},

    {0x14030200, "好的, 已打开"},
    {0x14030000, "好的, 已关闭"},

    {0x1C000100, "好的, 打开门锁"},

    {0x18000100, "好的, 打开电视"},
    {0x18000000, "好的, 关闭电视"},
    {0x18000200, "好的, 音量加大"},
    {0x18000300, "好的, 音量减小"},
    {0x18000400, "好的, 电视静音"},
    {0x18000500, "好的, 频道加"},
    {0x18000600, "好的, 频道减"},

    {0x1A240100, "好的, 打开勿扰"},
    {0x1A240000, "好的, 关闭勿扰"},
    {0x1A200100, "好的, 打开清理"},
    {0x1A200000, "好的, 关闭清理"},
};
struct TypingEffectContext {
    std::string full_text;
    size_t current_index = 0;
    lv_timer_t* typing_timer = nullptr;
    lv_timer_t* hide_timer = nullptr;
    int popup_alive_time = 3000;    // 弹窗自然存活时间
};
static TypingEffectContext typing_ctx;
void show_voice_popup(const std::string& text, int popup_alive_time = 3000);
static const uint8_t VOICE_WAKEUP[] = {0x88, 0x88, 0x88, 0x88, 0x88};

// 状态机的状态
typedef enum {
    WAIT_FOR_HEADER,
    RECEIVE_DATA,
    WAIT_FOR_FOOTER,
    PROCESS_DATA
} rs485_state_t;

void rs485_init(void) {
    const uart_config_t uart_config = {
        .baud_rate = RS485_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS, 
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    
    ESP_ERROR_CHECK(uart_param_config(RS485_UART_PORT, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(RS485_UART_PORT, RS485_TX_GPIO_NUM, RS485_RX_GPIO_NUM, RS485_DE_GPIO_NUM, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(RS485_UART_PORT, 1024 * 2, 0, 0, NULL, 0));

    ESP_ERROR_CHECK(uart_set_mode(RS485_UART_PORT, UART_MODE_RS485_HALF_DUPLEX));

    rs485Queue = xQueueCreate(RS485_QUEUE_LEN, sizeof(rs485_bus_cmd));
    if (rs485Queue == nullptr) {
        ESP_LOGE(TAG, "Failed to create RS485 command queue");
        return;
    }
    
    rs485_handle_semaphore = xSemaphoreCreateBinary();
    if (rs485_handle_semaphore == NULL) {
        ESP_LOGE(TAG, "创建信号量失败");
    }
    xSemaphoreGive(rs485_handle_semaphore);
    
    ESP_LOGI(TAG, "UART 1 初始化成功");

    // 心跳超时定时器
    heartbeat_timeout_timer = xTimerCreate("HeartbeatTimeout",
        pdMS_TO_TICKS(2000),
        pdFALSE,
        NULL,
        heartbeat_timeout_cb);
    xTimerReset(heartbeat_timeout_timer, 0);

    // 485发送
    xTaskCreate([](void* param) {
        rs485_bus_cmd cmd;
        while (true) {
            if (xQueueReceive(rs485Queue, &cmd, portMAX_DELAY) == pdPASS) {
                uart_write_bytes(RS485_UART_PORT, reinterpret_cast<const char*>(cmd.data), cmd.len);
                vTaskDelay(pdMS_TO_TICKS(100));
            }
        }
    }, "485_send_bus", 4096, nullptr, 5, nullptr);
    
    // 485接收
    xTaskCreate([](void* param) {
        uint8_t byte;
        int packet_size = 8;
        enum {
            WAIT_FOR_HEADER,
            RECEIVE_DATA,
        } state = WAIT_FOR_HEADER;

        uint8_t buffer[packet_size];
        int byte_index = 0;

        while (1) {
            // 读取单个字节
            int len = uart_read_bytes(RS485_UART_PORT, &byte, 1, portMAX_DELAY);
            if (len > 0) {
                switch (state) {
                    case WAIT_FOR_HEADER:
                        if (byte == PACKET_HEADER) {
                            state = RECEIVE_DATA;
                            byte_index = 0;
                            buffer[byte_index++] = byte;
                        } else {
                            ESP_LOGE(TAG, "错误包头: 0x%02x", byte);
                        }
                        break;

                    case RECEIVE_DATA:
                        buffer[byte_index++] = byte;
                        if (byte_index == packet_size) {
                            if ((buffer[0] == PACKET_HEADER && buffer[packet_size - 1] == PACKET_FOOTER))
                            handle_rs485_data(buffer, packet_size);
                            state = WAIT_FOR_HEADER; // 无论成功或失败，都重新等待下一帧
                        }
                        break;
                }
            } else if (len < 0) {
                ESP_LOGE(TAG, "UART 读取错误: %d", len);
            }
        }
        vTaskDelete(NULL);
    }, "485Receive task", 8192, NULL, 5, NULL);   
}

uint8_t calculate_checksum(const std::vector<uint8_t>& data) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < 6; ++i) {
        checksum += data[i];
    }
    return checksum & 0xFF;
}

static void handle_rs485_data(uint8_t* data, int length) {
    uint8_t checksum = calculate_checksum(std::vector<uint8_t>(data, data + 6));
    if (data[6] != checksum) {
        ESP_LOGE(TAG, "校验和错误: %d", checksum);
        for (size_t i = 0; i < 8; ++i) {
            printf("%02X ", data[i]);
        }
        printf("\n");
        return;
    }
    static const uint8_t CMD_HEARTBEAT[] = {0xC0, 0xFF, 0xFF, 0x00};
    if (memcmp(&data[1], CMD_HEARTBEAT, 4) != 0) {
        printf("485收到: ");
        for (size_t i = 0; i < 8; ++i) {
            printf("%02X ", data[i]);
        }
        printf("\n");
    }
        

    // 查询指令(心跳包)
    if (memcmp(&data[1], CMD_HEARTBEAT, 4) == 0) {
        xTimerReset(heartbeat_timeout_timer, 0);

        PanelManager::getInstance().report_all_state();
    }
    // RCU控制此面板的按钮的指示灯状态
    else if (data[1] == SWITCH_CONTROL) {
        uint8_t panel_id = data[3];
        uint8_t lights_byte = data[5];

        PanelManager::getInstance().update_lights(panel_id, lights_byte);
    }
    // 收到某处发出的空调信息, RCU或者温控器
    else if (data[1] == AIR_CON) {
        uint8_t state = data[4];
        // 无视不同id的信息
        if (get_var_air_id() != (state & 0x07)) return;
        uint8_t temps = data[5];

        uint8_t power = (state >> 7) & 0x01;                    // 空调开关
        uint8_t mode_bits = (state >> 5) & 0x03;                // 空调模式
        uint8_t fan_speed_bits = (state >> 3) & 0x03;           // 空调风速

        uint8_t target_temp_val = ((temps >> 4) & 0x0F) + 16;   // 目标温度
        uint8_t room_temp_val = ((temps >> 0) & 0x0F) + 16;     // 室温

        set_var_air_power(power);
        set_var_air_mode(bitsToMode(mode_bits));
        set_var_air_fan_speed(bitsToFanSpeed(fan_speed_bits));
        set_var_air_target_temp(target_temp_val);
        set_var_air_room_temp(room_temp_val);
    }
    // RCU同步时间
    else if (data[1] == TIME_SYNC) {
        time_t timestamp = ((time_t)data[2] << 24) |
            ((time_t)data[3] << 16) |
            ((time_t)data[4] << 8)  |
            (time_t)data[5];

        ClockManager::getInstance().init(timestamp);
        ClockManager::getInstance().attach_label(objects.now_time);
    }
    // 离线语音的唤醒
    else if (memcmp(&data[1], VOICE_WAKEUP, 5) == 0) {
        // 收到离线语音当然要点亮屏幕
        // action_click_wakeup(nullptr);
        reset_idle_monitor();

        lv_async_call([](void *param) {
            show_voice_popup("有什么可以帮助您?", 10000);
        }, nullptr);
    }
    // 离线语音
    else if (data[1] == OFFICE_VOICE) {
        // action_click_wakeup(nullptr);
        reset_idle_monitor();

        uint32_t opcode = (data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5];
        auto it = voice_response.find(opcode);
        if (it != voice_response.end()) {
            std::string message = it->second;
            lv_async_call([](void *param) {
                std::string *msg = static_cast<std::string*>(param);
                show_voice_popup(*msg);
                delete msg;
            }, new std::string(message));
        } else {
            ESP_LOGW(TAG, "未知语音码: 0x%08lX", opcode);
        }
    }

}

void sendRS485CMD(uint8_t param1, uint8_t param2, uint8_t param3, uint8_t param4, uint8_t param5) {
    std::vector<uint8_t> command = {
        PACKET_HEADER,
        param1,
        param2,
        param3,
        param4,
        param5,
        0x00,
        PACKET_FOOTER
    };

    command[6] = calculate_checksum(command);
    sendRS485CMD(command);
}

void sendRS485CMD(const std::vector<uint8_t>& data) {
    rs485_bus_cmd cmd;
    if (data.size() > RS485_CMD_MAX_LEN) {
        ESP_LOGE(TAG, "Data size (%d) exceeds RS485_CMD_MAX_LEN (%d), truncating", data.size(), RS485_CMD_MAX_LEN);
        cmd.len = RS485_CMD_MAX_LEN;
    } else {
        cmd.len = data.size();
    }
    memcpy(cmd.data, data.data(), cmd.len);
    if (xQueueSend(rs485Queue, &cmd, pdMS_TO_TICKS(3000)) != pdPASS) {
        ESP_LOGE(TAG, "Failed to send command to queue");
    }
    
    printf("发送包: ");
    for (int i = 0; i < RS485_CMD_MAX_LEN; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

// 心跳接收超时
void heartbeat_timeout_cb(TimerHandle_t xTimer) {
    // 丢弃所有panel的dirty标记
    PanelManager::getInstance().discard_all_state();
}


void show_voice_popup(const std::string& text, int popup_alive_time) {
    if (lv_obj_get_parent(objects.voice_response_popup) != lv_scr_act()) {
        lv_obj_set_parent(objects.voice_response_popup, lv_scr_act());
    }

    // 如果上一次打字还没打完，先清掉旧timer
    if (typing_ctx.typing_timer) {
        lv_timer_del(typing_ctx.typing_timer);
        typing_ctx.typing_timer = nullptr;
    }
    if (typing_ctx.hide_timer) {
        lv_timer_del(typing_ctx.hide_timer);
        typing_ctx.hide_timer = nullptr;
    }

    // 准备新的内容
    typing_ctx.full_text = text;
    typing_ctx.current_index = 0;
    typing_ctx.popup_alive_time = popup_alive_time;

    lv_label_set_text(objects.voice_response_label, ""); // 清空label
    lv_obj_clear_flag(objects.voice_response_popup, LV_OBJ_FLAG_HIDDEN);

    // 开始打字机效果
    typing_ctx.typing_timer = lv_timer_create([](lv_timer_t* t) {
        // 每次进来打一字
        if (typing_ctx.current_index < typing_ctx.full_text.size()) {
            std::string partial = typing_ctx.full_text.substr(0, typing_ctx.current_index + 1);
            lv_label_set_text(objects.voice_response_label, partial.c_str());
            typing_ctx.current_index++;
        } else {
            // 打完了
            lv_timer_del(typing_ctx.typing_timer);
            typing_ctx.typing_timer = nullptr;

            // 生存时间过后隐藏popup
            typing_ctx.hide_timer = lv_timer_create([](lv_timer_t* t_hide) {
                lv_obj_add_flag(objects.voice_response_popup, LV_OBJ_FLAG_HIDDEN);
                lv_timer_del(typing_ctx.hide_timer);
                typing_ctx.hide_timer = nullptr;
            }, typing_ctx.popup_alive_time, nullptr);
        }
    }, 40, nullptr);
}