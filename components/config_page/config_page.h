#pragma once
#include <vector>
#include <string>

#define MAX_LAMP_COUNT 12
#define MAX_CURTAIN_COUNT 6
#define MAX_MODE_COUNT 6


extern std::vector<lv_obj_t *> lamp_objs;
extern std::vector<lv_obj_t *> curtain_objs;
extern std::vector<lv_obj_t *> mode_objs;

struct ObjConfigInfo {
    const char* name;
    uint8_t panel_id;
    uint8_t button_id;
};

lv_obj_t *create_device_item(lv_obj_t *parent_obj);
ObjConfigInfo get_obj_config_info(const lv_obj_t* obj);