#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <vector>

// 配置参数
#define RS485_UART_PORT         UART_NUM_1
#define RS485_BAUD_RATE         9600
#define RS485_TX_GPIO_NUM       6
#define RS485_RX_GPIO_NUM       4
#define RS485_DE_GPIO_NUM       5

// 协议
#define PACKET_SIZE             8
#define PACKET_HEADER           0x7F
#define PACKET_FOOTER           0x7E

// 功能码
#define AIR_CON                 0x16    // 设备类型: 空调
#define AIR_CON_REPORT          0x08    // 同步空调状态给RCU
#define SWITCH_REPORT           0x00    // 本面板上报状态给RCU
#define SWITCH_CONTROL          0x01    // RCU操作本面板
#define TIME_SYNC               0x78    // RCU广播出来的时间
// 发送队列
#define RS485_CMD_MAX_LEN       8
#define RS485_QUEUE_LEN         10

// 发送包
struct rs485_bus_cmd {
    size_t len;
    uint8_t data[RS485_CMD_MAX_LEN];
};

// 接收包, 其实跟发送包的一样的结构
typedef struct {
    uint8_t header;
    uint8_t command[5];
    uint8_t checksum;
    uint8_t footer;
} rs485_packet_t;

// 初始化 RS485 接口
void rs485_init(void);
void sendRS485CMD(uint8_t param1, uint8_t param2, uint8_t param3, uint8_t param4, uint8_t param5);
void sendRS485CMD(const std::vector<uint8_t>& data);

static const uint8_t CMD_HEARTBEAT[] = {0xC0, 0xFF, 0xFF, 0x00, 0x80};