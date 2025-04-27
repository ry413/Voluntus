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

static const char *TAG = "RS485";

static QueueHandle_t rs485Queue = nullptr;
static SemaphoreHandle_t rs485_handle_semaphore = nullptr;
static void handle_rs485_data(uint8_t* data, int length);

TimerHandle_t heartbeat_timeout_timer = nullptr;
void heartbeat_timeout_cb(TimerHandle_t xTimer);

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
    if (memcmp(&data[1], CMD_HEARTBEAT, sizeof(CMD_HEARTBEAT)) != 0) {
        printf("485收到: ");
        for (size_t i = 0; i < 8; ++i) {
            printf("%02X ", data[i]);
        }
        printf("\n");
    }
        

    // 查询指令(心跳包)
    if (memcmp(&data[1], CMD_HEARTBEAT, sizeof(CMD_HEARTBEAT)) == 0) {
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