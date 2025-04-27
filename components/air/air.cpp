#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "air.h"
#include "vars.h"
#include "rs485.h"
#include "actions.h"

#define TAG "AIR"

static int32_t air_id;
static bool air_power = false;
static AIR_MODE air_mode;
static AIR_FAN_SPEED air_fan_speed;
static int32_t air_target_temp = 23;
static int32_t air_room_temp = 20;

// 防抖
static TimerHandle_t air_commit_timer = nullptr;
static bool air_dirty = false;

// 发送完整的空调信息到485
static void send_air_state_to_485() {
    uint8_t state =
        ((get_var_air_power() & 0x01) << 7) |
        ((modeToBits(get_var_air_mode()) & 0x03) << 5) |
        ((fanSpeedToBits(get_var_air_fan_speed()) & 0x03) << 3) |
        (air_id & 0x07);
    
    uint8_t temps =
        (((get_var_air_target_temp() - 16) & 0x0F) << 4) |
        ((air_room_temp - 16) & 0x0F);
    sendRS485CMD(AIR_CON, AIR_CON_REPORT, 0x00, state, temps);
}

void init_air_commit_timer() {
    air_commit_timer = xTimerCreate(
        "air_commit",
        pdMS_TO_TICKS(500),
        pdFALSE,
        NULL,
        [](TimerHandle_t){
            if (air_dirty) {
                air_dirty = false;
                send_air_state_to_485();
            }
        }
    );
}

// 重置防抖定时器
void schedule_air_commit() {
    air_dirty = true;
    if (air_commit_timer) {
        xTimerStop(air_commit_timer, 0);
        xTimerStart(air_commit_timer, 0);
    }
}

extern "C" bool get_var_air_power() {
    return air_power;
}

extern "C" void set_var_air_power(bool value) {
    air_power = value;
}

extern "C" AIR_MODE get_var_air_mode() {
    return air_mode;
}

extern "C" void set_var_air_mode(AIR_MODE value) {
    air_mode = value;
}

extern "C" AIR_FAN_SPEED get_var_air_fan_speed() {
    return air_fan_speed;
}

extern "C" void set_var_air_fan_speed(AIR_FAN_SPEED value) {
    air_fan_speed = value;
}

extern "C" int32_t get_var_air_target_temp() {
    return air_target_temp;
}

extern "C" void set_var_air_target_temp(int32_t value) {
    air_target_temp = value;
}

extern "C" int32_t get_var_air_room_temp() {
    return air_room_temp;
}

extern "C" void set_var_air_room_temp(int32_t value) {
    air_room_temp = value;
}

extern "C" int32_t get_var_air_id() {
    return air_id;
}

extern "C" void set_var_air_id(int32_t value) {
    air_id = value;
}

// **************** actions ****************

extern "C" void action_toggle_air_power(lv_event_t *e) {
    set_var_air_power(!get_var_air_power());
    schedule_air_commit();
}

extern "C" void action_toggle_air_mode(lv_event_t *e) {
    if (!get_var_air_power()) return;
    AIR_MODE new_mode = (AIR_MODE) ((get_var_air_mode() + 1) % AIR_MODE_COUNT);
    set_var_air_mode(new_mode);
    schedule_air_commit();
}

extern "C" void action_toggle_air_fan_speed(lv_event_t *e) {
    if (!get_var_air_power()) return;
    AIR_FAN_SPEED new_fan_speed = (AIR_FAN_SPEED) ((get_var_air_fan_speed() + 1) % AIR_FAN_SPEED_COUNT);
    set_var_air_fan_speed(new_fan_speed);
    schedule_air_commit();
}

extern "C" void action_add_temp(lv_event_t *e) {
    if (!get_var_air_power()) return;
    int temp = get_var_air_target_temp();
    if (temp < 31) {
        set_var_air_target_temp(temp + 1);
        schedule_air_commit();
    }
}

extern "C" void action_dec_temp(lv_event_t *e) {
    if (!get_var_air_power()) return;
    int temp = get_var_air_target_temp();
    if (temp > 16) {
        set_var_air_target_temp(temp - 1);
        schedule_air_commit();
    }
}

extern "C" void action_add_air_id(lv_event_t *e) {
    set_var_air_id(get_var_air_id() + 1);
}

extern "C" void action_dec_air_id(lv_event_t *e) {
    set_var_air_id(get_var_air_id() - 1);
}

extern "C" void action_reset_air_id(lv_event_t *e) {
    set_var_air_id(0);
}

AIR_MODE bitsToMode(uint8_t mode_bits) {
    switch (mode_bits) {
        case 0x00: return AIR_MODE_COOLING;
        case 0x01: return AIR_MODE_HOTING;
        case 0x03: return AIR_MODE_FAN;
        default: 
            ESP_LOGE(TAG, "未知模式位: 0x%2x", mode_bits);
            return AIR_MODE_COOLING;
    }
}

AIR_FAN_SPEED bitsToFanSpeed(uint8_t fan_speed_bits) {
    switch (fan_speed_bits) {
        case 0x00: return AIR_FAN_SPEED_LOW;
        case 0x01: return AIR_FAN_SPEED_MID;
        case 0x02: return AIR_FAN_SPEED_HIGH;
        case 0x03: return AIR_FAN_SPEED_AUTO;
        default: 
            ESP_LOGE(TAG, "未知风速位: 0x%2x", fan_speed_bits);
            return AIR_FAN_SPEED_LOW;
    }
}

uint8_t modeToBits(AIR_MODE mode) {
    switch (mode) {
        case AIR_MODE_COOLING: return 0x00;
        case AIR_MODE_HOTING:  return 0x01;
        case AIR_MODE_FAN:     return 0x03;
        default:
            ESP_LOGE(TAG, "未知模式: %d", static_cast<int>(mode));
            return 0x00;
    }
}

uint8_t fanSpeedToBits(AIR_FAN_SPEED fan_speed) {
    switch (fan_speed) {
        case AIR_FAN_SPEED_LOW:    return 0x00;
        case AIR_FAN_SPEED_MID:    return 0x01;
        case AIR_FAN_SPEED_HIGH:   return 0x02;
        case AIR_FAN_SPEED_AUTO:   return 0x03;
        default:
            ESP_LOGE(TAG, "未知风速: %d", static_cast<int>(fan_speed));
            return 0x00;
    }
}