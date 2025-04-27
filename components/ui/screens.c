#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_main(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        action_main_screen_loaded_cb(e);
    }
}

static void event_handler_cb_main_mode1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_main_mode2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_main_mode3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_main_mode4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_main_mode5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_main_mode6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_main_target_temp(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_scr_screen_to_config(e);
    }
}

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_toggle_air_power(e);
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_dec_temp(e);
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_add_temp(e);
    }
}

static void event_handler_cb_main_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_toggle_air_mode(e);
    }
}

static void event_handler_cb_main_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_toggle_air_fan_speed(e);
    }
}

static void event_handler_cb_main_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SHORT_CLICKED) {
        e->user_data = (void *)0;
        action_scr_screen_to_lamp(e);
    }
}

static void event_handler_cb_main_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SHORT_CLICKED) {
        e->user_data = (void *)0;
        action_scr_screen_to_curtain(e);
    }
}

static void event_handler_cb_config_config(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_UNLOADED) {
        e->user_data = (void *)0;
        action_store_configs(e);
    }
}

static void event_handler_cb_config_config_air_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_config_config_lamp_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_config_config_curtain_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_config_config_mode_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_config_obj7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_add_air_id(e);
    }
}

static void event_handler_cb_config_obj8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_dec_air_id(e);
    }
    if (event == LV_EVENT_LONG_PRESSED) {
        e->user_data = (void *)0;
        action_reset_air_id(e);
    }
}

static void event_handler_cb_config_obj9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_restart(e);
    }
}

static void event_handler_cb_config_page_number(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_clean_all_configs(e);
    }
}

static void event_handler_cb_config_obj10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_add_new_device(e);
    }
}

static void event_handler_cb_config_obj11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_prev_page(e);
    }
}

static void event_handler_cb_config_obj12(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_next_page(e);
    }
}

static void event_handler_cb_config_obj13(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SHORT_CLICKED) {
        e->user_data = (void *)0;
        action_scr_screen_to_main(e);
    }
}

static void event_handler_cb_lamp_control_obj14(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SHORT_CLICKED) {
        e->user_data = (void *)0;
        action_scr_screen_to_main(e);
    }
}

static void event_handler_cb_lamp_control_lamp1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_lamp_control_lamp12(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_curtain_control_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SHORT_CLICKED) {
        e->user_data = (void *)0;
        action_scr_screen_to_main(e);
    }
}

static void event_handler_cb_curtain_control_curtain1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_curtain_control_curtain2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_curtain_control_curtain3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_curtain_control_curtain4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_curtain_control_curtain5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_curtain_control_curtain6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        action_btn_touch(e);
    }
}

static void event_handler_cb_device_item_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_lamp_name_selector_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_exit_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj12(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj13(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj14(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_lamp_name_selector_obj16(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_delete_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj17(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_exit_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj18(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj19(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj20(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj21(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj22(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj23(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj24(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj25(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_curtain_name_selector_obj26(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_delete_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj27(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_exit_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj28(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj29(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj30(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj31(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj32(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj33(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj34(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj35(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj36(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_rename_device(e);
    }
}

static void event_handler_cb_mode_name_selector_obj37(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_delete_device(e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_add_event_cb(obj, event_handler_cb_main_main, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2e2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // modes_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.modes_container = obj;
            lv_obj_set_pos(obj, -7, 47);
            lv_obj_set_size(obj, 172, 433);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // mode1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mode1 = obj;
                    lv_obj_set_pos(obj, -2, 47);
                    lv_obj_set_size(obj, 142, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_mode1, LV_EVENT_ALL, flowState);
                    add_style_control_item_mode(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "睡眠模式");
                        }
                    }
                }
                {
                    // mode2
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mode2 = obj;
                    lv_obj_set_pos(obj, -2, 47);
                    lv_obj_set_size(obj, 142, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_mode2, LV_EVENT_ALL, flowState);
                    add_style_control_item_mode(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "睡眠模式");
                        }
                    }
                }
                {
                    // mode3
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mode3 = obj;
                    lv_obj_set_pos(obj, -2, 47);
                    lv_obj_set_size(obj, 142, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_mode3, LV_EVENT_ALL, flowState);
                    add_style_control_item_mode(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "睡眠模式");
                        }
                    }
                }
                {
                    // mode4
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mode4 = obj;
                    lv_obj_set_pos(obj, -2, 47);
                    lv_obj_set_size(obj, 142, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_mode4, LV_EVENT_ALL, flowState);
                    add_style_control_item_mode(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "睡眠模式");
                        }
                    }
                }
                {
                    // mode5
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mode5 = obj;
                    lv_obj_set_pos(obj, -2, 47);
                    lv_obj_set_size(obj, 142, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_mode5, LV_EVENT_ALL, flowState);
                    add_style_control_item_mode(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "睡眠模式");
                        }
                    }
                }
                {
                    // mode6
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.mode6 = obj;
                    lv_obj_set_pos(obj, -2, 47);
                    lv_obj_set_size(obj, 142, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_mode6, LV_EVENT_ALL, flowState);
                    add_style_control_item_mode(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "睡眠模式");
                        }
                    }
                }
            }
        }
        {
            // air_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.air_panel = obj;
            lv_obj_set_pos(obj, 165, 47);
            lv_obj_set_size(obj, 300, 323);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_normal_panel(obj);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.obj16 = obj;
                    lv_obj_set_pos(obj, -6, -5);
                    lv_obj_set_size(obj, 213, 125);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4e4d4d), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // air_mode
                            lv_obj_t *obj = lv_img_create(parent_obj);
                            objects.air_mode = obj;
                            lv_obj_set_pos(obj, 135, -9);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_img_set_src(obj, &img_mode_cooling);
                        }
                        {
                            // air_fan_speed
                            lv_obj_t *obj = lv_img_create(parent_obj);
                            objects.air_fan_speed = obj;
                            lv_obj_set_pos(obj, 135, 44);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_img_set_src(obj, &img_fan_mid);
                        }
                        {
                            // target_temp
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.target_temp = obj;
                            lv_obj_set_pos(obj, -4, 12);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_target_temp, LV_EVENT_ALL, flowState);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang78, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "23");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj17 = obj;
                            lv_obj_set_pos(obj, 88, 9);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang70, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "°");
                        }
                    }
                }
                {
                    // air_off_overlay
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.air_off_overlay = obj;
                    lv_obj_set_pos(obj, -6, -5);
                    lv_obj_set_size(obj, 213, 125);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4e4d4d), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 213, -5);
                    lv_obj_set_size(obj, 64, 125);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
                    add_style_test(obj);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_img_create(parent_obj);
                            lv_obj_set_pos(obj, 9, 53);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_img_set_src(obj, &img_power);
                        }
                    }
                }
                {
                    // falt1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.falt1 = obj;
                    lv_obj_set_pos(obj, -16, 227);
                    lv_obj_set_size(obj, 300, 80);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj1 = obj;
                            lv_obj_set_pos(obj, 250, 194);
                            lv_obj_set_size(obj, 150, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, flowState);
                            add_style_test(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_dec);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj2 = obj;
                            lv_obj_set_pos(obj, 248, 206);
                            lv_obj_set_size(obj, 150, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, flowState);
                            add_style_test(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff525252), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_add);
                                }
                            }
                        }
                    }
                }
                {
                    // flat2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.flat2 = obj;
                    lv_obj_set_pos(obj, -16, 153);
                    lv_obj_set_size(obj, 300, 80);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj3 = obj;
                            lv_obj_set_pos(obj, 123, 67);
                            lv_obj_set_size(obj, 150, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj3, LV_EVENT_ALL, flowState);
                            add_style_test(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 27, 35);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "M");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj4 = obj;
                            lv_obj_set_pos(obj, 74, -4);
                            lv_obj_set_size(obj, 150, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj4, LV_EVENT_ALL, flowState);
                            add_style_test(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // hell_2
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.hell_2 = obj;
                                    lv_obj_set_pos(obj, -8, -2);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_fan_speed_btn);
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 165, 382);
            lv_obj_set_size(obj, 137, 72);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj5, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_normal_panel(obj);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj18 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "灯光控制 >");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 329, 382);
            lv_obj_set_size(obj, 136, 72);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj6, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_normal_panel(obj);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj19 = obj;
                    lv_obj_set_pos(obj, 301, 394);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "窗帘控制 >");
                }
            }
        }
        {
            // room_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.room_temp = obj;
            lv_obj_set_pos(obj, 64, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // now_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.now_time = obj;
            lv_obj_set_pos(obj, 413, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj20 = obj;
            lv_obj_set_pos(obj, 10, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "室温:    °C");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_config() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.config = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_add_event_cb(obj, event_handler_cb_config_config, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2e2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // config_air_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.config_air_btn = obj;
            lv_obj_set_pos(obj, 0, 63);
            lv_obj_set_size(obj, 110, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_config_config_air_btn, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, -4, 18);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "空调配置");
                }
            }
        }
        {
            // config_lamp_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.config_lamp_btn = obj;
            lv_obj_set_pos(obj, 0, 144);
            lv_obj_set_size(obj, 110, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_config_config_lamp_btn, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4b5760), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, -4, 18);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "灯控配置");
                }
            }
        }
        {
            // config_curtain_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.config_curtain_btn = obj;
            lv_obj_set_pos(obj, 0, 225);
            lv_obj_set_size(obj, 110, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_config_config_curtain_btn, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, -4, 18);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "窗帘配置");
                }
            }
        }
        {
            // config_mode_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.config_mode_btn = obj;
            lv_obj_set_pos(obj, 0, 306);
            lv_obj_set_size(obj, 110, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_config_config_mode_btn, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "模式配置");
                }
            }
        }
        {
            // obj_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj_container = obj;
            lv_obj_set_pos(obj, 110, 40);
            lv_obj_set_size(obj, 370, 312);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // page_air
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_air = obj;
            lv_obj_set_pos(obj, 110, 0);
            lv_obj_set_size(obj, 370, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj21 = obj;
                    lv_obj_set_pos(obj, 155, 28);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "空调ID");
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 255, 59);
                    lv_obj_set_size(obj, 70, 70);
                    lv_obj_add_event_cb(obj, event_handler_cb_config_obj7, LV_EVENT_ALL, flowState);
                    add_style_round_button(obj);
                    lv_obj_set_style_radius(obj, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj25 = obj;
                            lv_obj_set_pos(obj, -109, 5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 131, 68);
                    lv_obj_set_size(obj, 113, 52);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // air_id
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.air_id = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, 49, 59);
                    lv_obj_set_size(obj, 70, 70);
                    lv_obj_add_event_cb(obj, event_handler_cb_config_obj8, LV_EVENT_ALL, flowState);
                    add_style_round_button(obj);
                    lv_obj_set_style_radius(obj, 40, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj26 = obj;
                            lv_obj_set_pos(obj, 0, -18);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
        {
            // config_table_header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.config_table_header = obj;
            lv_obj_set_pos(obj, 110, 0);
            lv_obj_set_size(obj, 370, 40);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj22 = obj;
                    lv_obj_set_pos(obj, 27, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "名称");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj23 = obj;
                    lv_obj_set_pos(obj, 164, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "面板ID");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj9 = obj;
                    lv_obj_set_pos(obj, 286, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_event_cb(obj, event_handler_cb_config_obj9, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "按钮ID");
                }
            }
        }
        {
            // page_number
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.page_number = obj;
            lv_obj_set_pos(obj, 280, 352);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_add_event_cb(obj, event_handler_cb_config_page_number, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ping_fang18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "1/1");
        }
        {
            // config_table_footer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.config_table_footer = obj;
            lv_obj_set_pos(obj, 110, 372);
            lv_obj_set_size(obj, 370, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj10 = obj;
                    lv_obj_set_pos(obj, 1987, 36);
                    lv_obj_set_size(obj, 131, 80);
                    lv_obj_add_event_cb(obj, event_handler_cb_config_obj10, LV_EVENT_ALL, flowState);
                    add_style_round_button(obj);
                    lv_obj_set_style_radius(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 100, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "新建");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, -6582, 0);
                    lv_obj_set_size(obj, 38, 80);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj11 = obj;
                    lv_obj_set_pos(obj, 174, 36);
                    lv_obj_set_size(obj, 80, 80);
                    lv_obj_add_event_cb(obj, event_handler_cb_config_obj11, LV_EVENT_ALL, flowState);
                    add_style_round_button(obj);
                    lv_obj_set_style_radius(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "上一页");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj12 = obj;
                    lv_obj_set_pos(obj, 271, 36);
                    lv_obj_set_size(obj, 80, 80);
                    lv_obj_add_event_cb(obj, event_handler_cb_config_obj12, LV_EVENT_ALL, flowState);
                    add_style_round_button(obj);
                    lv_obj_set_style_radius(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "下一页");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 110, 57);
            lv_obj_add_event_cb(obj, event_handler_cb_config_obj13, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "返回");
                }
            }
        }
        {
            // mode_name_selector
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mode_name_selector = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_mode_name_selector(obj, getFlowState(flowState, 33), 5);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        {
            // curtain_name_selector
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.curtain_name_selector = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_curtain_name_selector(obj, getFlowState(flowState, 34), 18);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        {
            // lamp_name_selector
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.lamp_name_selector = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_lamp_name_selector(obj, getFlowState(flowState, 35), 29);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj24 = obj;
            lv_obj_set_pos(obj, 5, 460);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ping_fang14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "v1.0.0-Initiatio");
        }
    }
    
    tick_screen_config();
}

void tick_screen_config() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj25);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj25;
            lv_label_set_text(objects.obj25, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj26);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj26;
            lv_label_set_text(objects.obj26, new_val);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_mode_name_selector(getFlowState(flowState, 33), 5);
    tick_user_widget_curtain_name_selector(getFlowState(flowState, 34), 18);
    tick_user_widget_lamp_name_selector(getFlowState(flowState, 35), 29);
}

void create_screen_lamp_control() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.lamp_control = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2e2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj14 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 110, 57);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_obj14, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "返回");
                }
            }
        }
        {
            // lamp1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp1 = obj;
            lv_obj_set_pos(obj, 18, 90);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp1, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp2 = obj;
            lv_obj_set_pos(obj, 133, 90);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp2, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp3 = obj;
            lv_obj_set_pos(obj, 248, 90);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp3, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp4 = obj;
            lv_obj_set_pos(obj, 363, 90);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp4, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp5 = obj;
            lv_obj_set_pos(obj, 18, 219);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp5, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp6 = obj;
            lv_obj_set_pos(obj, 133, 219);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp6, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp7
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp7 = obj;
            lv_obj_set_pos(obj, 248, 219);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp7, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp8
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp8 = obj;
            lv_obj_set_pos(obj, 363, 219);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp8, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp9
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp9 = obj;
            lv_obj_set_pos(obj, 18, 351);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp9, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp10
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp10 = obj;
            lv_obj_set_pos(obj, 133, 351);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp10, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp11
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp11 = obj;
            lv_obj_set_pos(obj, 248, 351);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp11, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // lamp12
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.lamp12 = obj;
            lv_obj_set_pos(obj, 363, 351);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_lamp_control_lamp12, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
    }
    
    tick_screen_lamp_control();
}

void tick_screen_lamp_control() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
}

void create_screen_curtain_control() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.curtain_control = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2e2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj15 = obj;
            lv_obj_set_pos(obj, 0, 1);
            lv_obj_set_size(obj, 110, 57);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_obj15, LV_EVENT_ALL, flowState);
            add_style_config_tab(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "返回");
                }
            }
        }
        {
            // curtain1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.curtain1 = obj;
            lv_obj_set_pos(obj, 20, 104);
            lv_obj_set_size(obj, 130, 130);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_curtain1, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // curtain2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.curtain2 = obj;
            lv_obj_set_pos(obj, 175, 104);
            lv_obj_set_size(obj, 130, 130);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_curtain2, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // curtain3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.curtain3 = obj;
            lv_obj_set_pos(obj, 330, 104);
            lv_obj_set_size(obj, 130, 130);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_curtain3, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // curtain4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.curtain4 = obj;
            lv_obj_set_pos(obj, 21, 269);
            lv_obj_set_size(obj, 130, 130);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_curtain4, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // curtain5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.curtain5 = obj;
            lv_obj_set_pos(obj, 176, 269);
            lv_obj_set_size(obj, 130, 130);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_curtain5, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            // curtain6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.curtain6 = obj;
            lv_obj_set_pos(obj, 331, 269);
            lv_obj_set_size(obj, 130, 130);
            lv_obj_add_event_cb(obj, event_handler_cb_curtain_control_curtain6, LV_EVENT_ALL, flowState);
            add_style_control_item_lamp(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_control_btn(obj);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
    }
    
    tick_screen_curtain_control();
}

void tick_screen_curtain_control() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
}

void create_user_widget_device_item(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 370, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff606060), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, -6, -10);
                    lv_obj_set_size(obj, 100, 60);
                    lv_obj_add_event_cb(obj, event_handler_cb_device_item_obj0, LV_EVENT_ALL, flowState);
                    add_style_test(obj);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "点此命名");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 140, -16);
                    lv_obj_set_size(obj, 80, 70);
                    lv_roller_set_options(obj, "0\n1", LV_ROLLER_MODE_INFINITE);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_SELECTED | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    lv_obj_set_pos(obj, 262, -16);
                    lv_obj_set_size(obj, 80, 70);
                    lv_roller_set_options(obj, "6\n7", LV_ROLLER_MODE_INFINITE);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_user_widget_device_item(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_lamp_name_selector(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 480, 480);
                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj3, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_popup_window_background(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 44, 80);
                            lv_obj_set_size(obj, 357, 300);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_grow(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj4, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "天花灯带");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj5, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "镜前灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj6, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "廊灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj7, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "沙发灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj8, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "床头灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj9, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "左床头灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj10, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "右床头灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj11, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "浴室灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj12, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "床头射灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj13, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "天花射灯");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj14, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "床下灯带");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj15, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "盆下灯带");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                            lv_obj_set_pos(obj, 351, -16);
                            lv_obj_set_size(obj, 113, 60);
                            lv_obj_add_event_cb(obj, event_handler_cb_lamp_name_selector_obj16, LV_EVENT_ALL, flowState);
                            add_style_delete_device(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "删除");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_lamp_name_selector(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_curtain_name_selector(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 480, 480);
                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj17, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_popup_window_background(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 44, 80);
                            lv_obj_set_size(obj, 357, 300);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_grow(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj18, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "窗帘开");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj19, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "窗帘关");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj20, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "窗纱开");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj21, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "窗纱关");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj22, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "客厅窗帘开");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj23, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "客厅窗帘关");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                                    lv_obj_set_pos(obj, -396, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj24, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "客厅窗纱开");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 120, 65);
                                    lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj25, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "客厅窗纱关");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 351, -16);
                            lv_obj_set_size(obj, 113, 60);
                            lv_obj_add_event_cb(obj, event_handler_cb_curtain_name_selector_obj26, LV_EVENT_ALL, flowState);
                            add_style_delete_device(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "删除");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_curtain_name_selector(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}

void create_user_widget_mode_name_selector(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // selector_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 480, 480);
                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj27, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_popup_window_background(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 44, 80);
                            lv_obj_set_size(obj, 357, 300);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_grow(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj28, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "明亮模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj29, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "阅读模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj30, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "睡眠模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj31, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "影音模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj32, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "电视模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj33, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "全开模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj34, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "全关模式");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj35, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "全开/关");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 100, 70);
                                    lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj36, LV_EVENT_ALL, flowState);
                                    add_style_lamp_name_item(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "浴室模式");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                            lv_obj_set_pos(obj, 351, -16);
                            lv_obj_set_size(obj, 113, 60);
                            lv_obj_add_event_cb(obj, event_handler_cb_mode_name_selector_obj37, LV_EVENT_ALL, flowState);
                            add_style_delete_device(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "删除");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_mode_name_selector(void *flowState, int startWidgetIndex) {
    (void)flowState;
    (void)startWidgetIndex;
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "Main", "config", "lamp_control", "curtain_control" };
static const char *object_names[] = { "main", "config", "lamp_control", "curtain_control", "mode_name_selector", "mode_name_selector__obj27", "mode_name_selector__obj28", "mode_name_selector__obj29", "mode_name_selector__obj30", "mode_name_selector__obj31", "mode_name_selector__obj32", "mode_name_selector__obj33", "mode_name_selector__obj34", "mode_name_selector__obj35", "mode_name_selector__obj36", "mode_name_selector__obj37", "mode_name_selector__selector_2", "curtain_name_selector", "curtain_name_selector__obj17", "curtain_name_selector__obj18", "curtain_name_selector__obj19", "curtain_name_selector__obj20", "curtain_name_selector__obj21", "curtain_name_selector__obj22", "curtain_name_selector__obj23", "curtain_name_selector__obj24", "curtain_name_selector__obj25", "curtain_name_selector__obj26", "lamp_name_selector", "lamp_name_selector__obj3", "lamp_name_selector__obj4", "lamp_name_selector__obj5", "lamp_name_selector__obj6", "lamp_name_selector__obj7", "lamp_name_selector__obj8", "lamp_name_selector__obj9", "lamp_name_selector__obj10", "lamp_name_selector__obj11", "lamp_name_selector__obj12", "lamp_name_selector__obj13", "lamp_name_selector__obj14", "lamp_name_selector__obj15", "lamp_name_selector__obj16", "mode1", "mode2", "mode3", "mode4", "mode5", "mode6", "target_temp", "obj0", "obj1", "obj2", "obj3", "obj4", "obj5", "obj6", "config_air_btn", "config_lamp_btn", "config_curtain_btn", "config_mode_btn", "obj7", "obj8", "obj9", "page_number", "obj10", "obj11", "obj12", "obj13", "obj14", "lamp1", "lamp2", "lamp3", "lamp4", "lamp5", "lamp6", "lamp7", "lamp8", "lamp9", "lamp10", "lamp11", "lamp12", "obj15", "curtain1", "curtain2", "curtain3", "curtain4", "curtain5", "curtain6", "modes_container", "air_panel", "obj16", "air_mode", "air_fan_speed", "obj17", "air_off_overlay", "falt1", "flat2", "hell_2", "obj18", "obj19", "room_temp", "now_time", "obj20", "obj_container", "page_air", "obj21", "air_id", "config_table_header", "obj22", "obj23", "config_table_footer", "obj24", "obj25", "obj26" };
static const char *style_names[] = { "Center Icon", "Round Button", "Normal Button", "control_item_mode", "Normal Panel", "test", "config_tab", "lamp_name_item", "control_item_lamp", "control_btn", "delete_device", "popup window background" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_config,
    tick_screen_lamp_control,
    tick_screen_curtain_control,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_config();
    create_screen_lamp_control();
    create_screen_curtain_control();
}
