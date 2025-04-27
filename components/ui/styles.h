#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: Center Icon
lv_style_t *get_style_center_icon_MAIN_DEFAULT();
void add_style_center_icon(lv_obj_t *obj);
void remove_style_center_icon(lv_obj_t *obj);

// Style: Round Button
lv_style_t *get_style_round_button_MAIN_DEFAULT();
void add_style_round_button(lv_obj_t *obj);
void remove_style_round_button(lv_obj_t *obj);

// Style: Normal Button
lv_style_t *get_style_normal_button_MAIN_DEFAULT();
void add_style_normal_button(lv_obj_t *obj);
void remove_style_normal_button(lv_obj_t *obj);

// Style: control_item_mode
lv_style_t *get_style_control_item_mode_MAIN_CHECKED();
lv_style_t *get_style_control_item_mode_MAIN_DEFAULT();
void add_style_control_item_mode(lv_obj_t *obj);
void remove_style_control_item_mode(lv_obj_t *obj);

// Style: Normal Panel
lv_style_t *get_style_normal_panel_MAIN_DEFAULT();
void add_style_normal_panel(lv_obj_t *obj);
void remove_style_normal_panel(lv_obj_t *obj);

// Style: test
lv_style_t *get_style_test_MAIN_DEFAULT();
void add_style_test(lv_obj_t *obj);
void remove_style_test(lv_obj_t *obj);

// Style: config_tab
lv_style_t *get_style_config_tab_MAIN_DEFAULT();
lv_style_t *get_style_config_tab_MAIN_CHECKED();
void add_style_config_tab(lv_obj_t *obj);
void remove_style_config_tab(lv_obj_t *obj);

// Style: lamp_name_item
lv_style_t *get_style_lamp_name_item_MAIN_DEFAULT();
void add_style_lamp_name_item(lv_obj_t *obj);
void remove_style_lamp_name_item(lv_obj_t *obj);

// Style: control_item_lamp
lv_style_t *get_style_control_item_lamp_MAIN_DEFAULT();
lv_style_t *get_style_control_item_lamp_MAIN_CHECKED();
void add_style_control_item_lamp(lv_obj_t *obj);
void remove_style_control_item_lamp(lv_obj_t *obj);

// Style: control_btn
lv_style_t *get_style_control_btn_MAIN_DEFAULT();
void add_style_control_btn(lv_obj_t *obj);
void remove_style_control_btn(lv_obj_t *obj);

// Style: delete_device
lv_style_t *get_style_delete_device_MAIN_DEFAULT();
void add_style_delete_device(lv_obj_t *obj);
void remove_style_delete_device(lv_obj_t *obj);

// Style: popup window background
lv_style_t *get_style_popup_window_background_MAIN_DEFAULT();
void add_style_popup_window_background(lv_obj_t *obj);
void remove_style_popup_window_background(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/