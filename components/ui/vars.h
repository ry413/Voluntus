#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

typedef enum {
    AIR_MODE_COOLING = 0,
    AIR_MODE_HOTING = 1,
    AIR_MODE_FAN = 2,
    AIR_MODE_COUNT = 3
} AIR_MODE;

typedef enum {
    AIR_FAN_SPEED_LOW = 0,
    AIR_FAN_SPEED_MID = 1,
    AIR_FAN_SPEED_HIGH = 2,
    AIR_FAN_SPEED_AUTO = 3,
    AIR_FAN_SPEED_COUNT = 4
} AIR_FAN_SPEED;

typedef enum {
    ACTIVE_CONFIG_PAGE_AIR = 0,
    ACTIVE_CONFIG_PAGE_LAMP = 1,
    ACTIVE_CONFIG_PAGE_CURTAIN = 2,
    ACTIVE_CONFIG_PAGE_MODE = 3,
    ACTIVE_CONFIG_PAGE_COUNT = 4
} ACTIVE_CONFIG_PAGE;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern AIR_FAN_SPEED get_var_air_fan_speed();
extern void set_var_air_fan_speed(AIR_FAN_SPEED value);
extern AIR_MODE get_var_air_mode();
extern void set_var_air_mode(AIR_MODE value);
extern bool get_var_air_power();
extern void set_var_air_power(bool value);
extern int32_t get_var_air_target_temp();
extern void set_var_air_target_temp(int32_t value);
extern int32_t get_var_air_room_temp();
extern void set_var_air_room_temp(int32_t value);
extern int32_t get_var_air_id();
extern void set_var_air_id(int32_t value);
extern ACTIVE_CONFIG_PAGE get_var_active_config_page();
extern void set_var_active_config_page(ACTIVE_CONFIG_PAGE value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/