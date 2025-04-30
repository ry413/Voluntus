#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_toggle_air_mode(lv_event_t * e);
extern void action_toggle_air_fan_speed(lv_event_t * e);
extern void action_toggle_air_power(lv_event_t * e);
extern void action_add_temp(lv_event_t * e);
extern void action_dec_temp(lv_event_t * e);
extern void action_add_air_id(lv_event_t * e);
extern void action_dec_air_id(lv_event_t * e);
extern void action_reset_air_id(lv_event_t * e);
extern void action_change_config_page(lv_event_t * e);
extern void action_begin_rename_device(lv_event_t * e);
extern void action_rename_device(lv_event_t * e);
extern void action_exit_rename_device(lv_event_t * e);
extern void action_add_new_device(lv_event_t * e);
extern void action_next_page(lv_event_t * e);
extern void action_prev_page(lv_event_t * e);
extern void action_delete_device(lv_event_t * e);
extern void action_scr_screen_to_main(lv_event_t * e);
extern void action_scr_screen_to_lamp(lv_event_t * e);
extern void action_scr_screen_to_curtain(lv_event_t * e);
extern void action_scr_screen_to_config(lv_event_t * e);
extern void action_btn_touch(lv_event_t * e);
extern void action_main_screen_loaded_cb(lv_event_t * e);
extern void action_store_configs(lv_event_t * e);
extern void action_clean_all_configs(lv_event_t * e);
extern void action_restart(lv_event_t * e);
extern void action_close_voice_response_popup(lv_event_t * e);
extern void action_click_wakeup(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/