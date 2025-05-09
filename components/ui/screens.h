#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *config;
    lv_obj_t *lamp_control;
    lv_obj_t *curtain_control;
    lv_obj_t *mode_name_selector;
    lv_obj_t *mode_name_selector__obj27;
    lv_obj_t *mode_name_selector__obj28;
    lv_obj_t *mode_name_selector__obj29;
    lv_obj_t *mode_name_selector__obj30;
    lv_obj_t *mode_name_selector__obj31;
    lv_obj_t *mode_name_selector__obj32;
    lv_obj_t *mode_name_selector__obj33;
    lv_obj_t *mode_name_selector__obj34;
    lv_obj_t *mode_name_selector__obj35;
    lv_obj_t *mode_name_selector__obj36;
    lv_obj_t *mode_name_selector__obj37;
    lv_obj_t *mode_name_selector__selector_2;
    lv_obj_t *curtain_name_selector;
    lv_obj_t *curtain_name_selector__obj17;
    lv_obj_t *curtain_name_selector__obj18;
    lv_obj_t *curtain_name_selector__obj19;
    lv_obj_t *curtain_name_selector__obj20;
    lv_obj_t *curtain_name_selector__obj21;
    lv_obj_t *curtain_name_selector__obj22;
    lv_obj_t *curtain_name_selector__obj23;
    lv_obj_t *curtain_name_selector__obj24;
    lv_obj_t *curtain_name_selector__obj25;
    lv_obj_t *curtain_name_selector__obj26;
    lv_obj_t *lamp_name_selector;
    lv_obj_t *lamp_name_selector__obj3;
    lv_obj_t *lamp_name_selector__obj4;
    lv_obj_t *lamp_name_selector__obj5;
    lv_obj_t *lamp_name_selector__obj6;
    lv_obj_t *lamp_name_selector__obj7;
    lv_obj_t *lamp_name_selector__obj8;
    lv_obj_t *lamp_name_selector__obj9;
    lv_obj_t *lamp_name_selector__obj10;
    lv_obj_t *lamp_name_selector__obj11;
    lv_obj_t *lamp_name_selector__obj12;
    lv_obj_t *lamp_name_selector__obj13;
    lv_obj_t *lamp_name_selector__obj14;
    lv_obj_t *lamp_name_selector__obj15;
    lv_obj_t *lamp_name_selector__obj16;
    lv_obj_t *mode1;
    lv_obj_t *mode2;
    lv_obj_t *mode3;
    lv_obj_t *mode4;
    lv_obj_t *mode5;
    lv_obj_t *mode6;
    lv_obj_t *target_temp;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *voice_response_popup;
    lv_obj_t *idle_overlay;
    lv_obj_t *obj7;
    lv_obj_t *config_air_btn;
    lv_obj_t *config_lamp_btn;
    lv_obj_t *config_curtain_btn;
    lv_obj_t *config_mode_btn;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *page_number;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *lamp1;
    lv_obj_t *lamp2;
    lv_obj_t *lamp3;
    lv_obj_t *lamp4;
    lv_obj_t *lamp5;
    lv_obj_t *lamp6;
    lv_obj_t *lamp7;
    lv_obj_t *lamp8;
    lv_obj_t *lamp9;
    lv_obj_t *lamp10;
    lv_obj_t *lamp11;
    lv_obj_t *lamp12;
    lv_obj_t *obj16;
    lv_obj_t *curtain1;
    lv_obj_t *curtain2;
    lv_obj_t *curtain3;
    lv_obj_t *curtain4;
    lv_obj_t *curtain5;
    lv_obj_t *curtain6;
    lv_obj_t *modes_container;
    lv_obj_t *air_panel;
    lv_obj_t *obj17;
    lv_obj_t *air_mode;
    lv_obj_t *air_fan_speed;
    lv_obj_t *obj18;
    lv_obj_t *air_off_overlay;
    lv_obj_t *falt1;
    lv_obj_t *flat2;
    lv_obj_t *hell_2;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *room_temp;
    lv_obj_t *now_time;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *voice_response_label;
    lv_obj_t *idle_screen_container;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *idle_screen_time_label;
    lv_obj_t *idle_screen_time_decora;
    lv_obj_t *main_screen_time_decora;
    lv_obj_t *obj_container;
    lv_obj_t *page_air;
    lv_obj_t *obj34;
    lv_obj_t *air_id;
    lv_obj_t *config_table_header;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *config_table_footer;
    lv_obj_t *version;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_CONFIG = 2,
    SCREEN_ID_LAMP_CONTROL = 3,
    SCREEN_ID_CURTAIN_CONTROL = 4,
};

void create_screen_main();
void tick_screen_main();

void create_screen_config();
void tick_screen_config();

void create_screen_lamp_control();
void tick_screen_lamp_control();

void create_screen_curtain_control();
void tick_screen_curtain_control();

void create_user_widget_device_item(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_device_item(void *flowState, int startWidgetIndex);

void create_user_widget_lamp_name_selector(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_lamp_name_selector(void *flowState, int startWidgetIndex);

void create_user_widget_curtain_name_selector(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_curtain_name_selector(void *flowState, int startWidgetIndex);

void create_user_widget_mode_name_selector(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_mode_name_selector(void *flowState, int startWidgetIndex);

void create_user_widget_voice_response_popup(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_voice_response_popup(void *flowState, int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/