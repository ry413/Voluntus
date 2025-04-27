#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: Center Icon
//

void init_style_center_icon_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 25);
    lv_style_set_bg_color(style, lv_color_hex(0xff282828));
    lv_style_set_shadow_width(style, 20);
    lv_style_set_shadow_ofs_x(style, 2);
    lv_style_set_shadow_ofs_y(style, 2);
    lv_style_set_shadow_spread(style, 2);
    lv_style_set_shadow_color(style, lv_color_hex(0xff000000));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_side(style, LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT);
    lv_style_set_border_color(style, lv_color_hex(0xff5b5b5b));
    lv_style_set_outline_opa(style, 127);
    lv_style_set_outline_width(style, 1);
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_track_place(style, LV_FLEX_ALIGN_CENTER);
};

lv_style_t *get_style_center_icon_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_center_icon_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_center_icon(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_center_icon_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_center_icon(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_center_icon_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Round Button
//

void init_style_round_button_MAIN_DEFAULT(lv_style_t *style) {
    init_style_center_icon_MAIN_DEFAULT(style);
    
    lv_style_set_outline_width(style, 3);
    lv_style_set_border_color(style, lv_color_hex(0xff5b5b5b));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 30);
};

lv_style_t *get_style_round_button_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_round_button_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_round_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_round_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_round_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_round_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Normal Button
//

void init_style_normal_button_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_shadow_width(style, 20);
    lv_style_set_shadow_ofs_x(style, 2);
    lv_style_set_shadow_color(style, lv_color_hex(0xff000000));
    lv_style_set_bg_color(style, lv_color_hex(0xff242425));
    lv_style_set_border_color(style, lv_color_hex(0xff5b5b5b));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_side(style, LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT);
    lv_style_set_shadow_ofs_y(style, 2);
    lv_style_set_shadow_spread(style, 2);
};

lv_style_t *get_style_normal_button_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_normal_button_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_normal_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_normal_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_normal_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_normal_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: control_item_mode
//

void init_style_control_item_mode_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffa5a5a5));
};

lv_style_t *get_style_control_item_mode_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_control_item_mode_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_control_item_mode_MAIN_DEFAULT(lv_style_t *style) {
    init_style_normal_button_MAIN_DEFAULT(style);
    
};

lv_style_t *get_style_control_item_mode_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_control_item_mode_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_control_item_mode(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_control_item_mode_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_control_item_mode_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_control_item_mode(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_control_item_mode_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_control_item_mode_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Normal Panel
//

void init_style_normal_panel_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff242425));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_color(style, lv_color_hex(0xff5b5b5b));
    lv_style_set_border_side(style, LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT);
    lv_style_set_shadow_width(style, 20);
    lv_style_set_shadow_ofs_x(style, 2);
    lv_style_set_shadow_ofs_y(style, 2);
    lv_style_set_shadow_spread(style, 2);
    lv_style_set_shadow_color(style, lv_color_hex(0xff000000));
    lv_style_set_shadow_opa(style, 255);
    lv_style_set_radius(style, 17);
    lv_style_set_outline_width(style, 1);
};

lv_style_t *get_style_normal_panel_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_normal_panel_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_normal_panel(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_normal_panel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_normal_panel(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_normal_panel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: test
//

void init_style_test_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_track_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_radius(style, 0);
    lv_style_set_outline_width(style, 1);
    lv_style_set_bg_color(style, lv_color_hex(0xff525252));
};

lv_style_t *get_style_test_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_test_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_test(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_test_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_test(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_test_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: config_tab
//

void init_style_config_tab_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff4b5760));
    lv_style_set_radius(style, 0);
    lv_style_set_border_width(style, 1);
    lv_style_set_border_side(style, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_RIGHT);
    lv_style_set_shadow_width(style, 0);
};

lv_style_t *get_style_config_tab_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_config_tab_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_config_tab_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffa5a5a5));
};

lv_style_t *get_style_config_tab_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_config_tab_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_config_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_config_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_config_tab_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_config_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_config_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_config_tab_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: lamp_name_item
//

void init_style_lamp_name_item_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff54748d));
};

lv_style_t *get_style_lamp_name_item_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_lamp_name_item_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_lamp_name_item(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_lamp_name_item_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_lamp_name_item(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_lamp_name_item_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: control_item_lamp
//

void init_style_control_item_lamp_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff4b5760));
    lv_style_set_shadow_width(style, 0);
};

lv_style_t *get_style_control_item_lamp_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_control_item_lamp_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_control_item_lamp_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffa5a5a5));
};

lv_style_t *get_style_control_item_lamp_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_control_item_lamp_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_control_item_lamp(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_control_item_lamp_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_control_item_lamp_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_control_item_lamp(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_control_item_lamp_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_control_item_lamp_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: control_btn
//

void init_style_control_btn_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_font(style, &ui_font_ping_fang22);
};

lv_style_t *get_style_control_btn_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_control_btn_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_control_btn(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_control_btn_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_control_btn(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_control_btn_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: delete_device
//

void init_style_delete_device_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
    lv_style_set_shadow_width(style, 0);
};

lv_style_t *get_style_delete_device_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_delete_device_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_delete_device(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_delete_device_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_delete_device(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_delete_device_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: popup window background
//

void init_style_popup_window_background_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
    lv_style_set_bg_opa(style, 153);
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_popup_window_background_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_popup_window_background_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_popup_window_background(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_popup_window_background_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_popup_window_background(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_popup_window_background_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_center_icon,
        add_style_round_button,
        add_style_normal_button,
        add_style_control_item_mode,
        add_style_normal_panel,
        add_style_test,
        add_style_config_tab,
        add_style_lamp_name_item,
        add_style_control_item_lamp,
        add_style_control_btn,
        add_style_delete_device,
        add_style_popup_window_background,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_center_icon,
        remove_style_round_button,
        remove_style_normal_button,
        remove_style_control_item_mode,
        remove_style_normal_panel,
        remove_style_test,
        remove_style_config_tab,
        remove_style_lamp_name_item,
        remove_style_control_item_lamp,
        remove_style_control_btn,
        remove_style_delete_device,
        remove_style_popup_window_background,
    };
    remove_style_funcs[styleIndex](obj);
}

