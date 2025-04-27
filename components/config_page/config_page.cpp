#include "vars.h"
#include "actions.h"
#include "screens.h"
#include "ui.h"
#include "eez-flow.h"
#include "config_page.h"
#include <memory>
#include <stdio.h>
#include "styles.h"
#include "fonts.h"
#include "esp_log.h"
#include <algorithm>
#include "utils.h"

#define TAG "CONFIG_PAGE"

static lv_obj_t *current_rename_label;          // 重命名时, 唤出选择器的来源label
static ACTIVE_CONFIG_PAGE active_config_page;   // 当前配置类型
static int current_page = 0;                    // 设备列表的当前页
static constexpr int ITEMS_PER_PAGE = 4;        // 一页显示几项

// 这些objs纯属UI, 并不储存ObjConfigInfo
std::vector<lv_obj_t *> lamp_objs;
std::vector<lv_obj_t *> curtain_objs;
std::vector<lv_obj_t *> mode_objs;

static void refresh_page();
static std::vector<lv_obj_t*> &get_current_vector();

extern "C" ACTIVE_CONFIG_PAGE get_var_active_config_page() {
    return active_config_page;
}

extern "C" void set_var_active_config_page(ACTIVE_CONFIG_PAGE value) {
    active_config_page = value;
}

extern "C" void action_change_config_page(lv_event_t *e) {
    lv_obj_clear_state(objects.config_lamp_btn, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.config_air_btn, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.config_curtain_btn, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.config_mode_btn, LV_STATE_CHECKED);

    if (active_config_page == ACTIVE_CONFIG_PAGE_AIR) {
        lv_obj_add_state(objects.config_air_btn, LV_STATE_CHECKED);
        lv_obj_clear_flag(objects.page_air, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.config_table_header, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.config_table_footer, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.page_number, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.obj_container, LV_OBJ_FLAG_HIDDEN);
        
    } else {
        switch (active_config_page) {
            case ACTIVE_CONFIG_PAGE_LAMP:
                lv_obj_add_state(objects.config_lamp_btn, LV_STATE_CHECKED);
                break;
            case ACTIVE_CONFIG_PAGE_CURTAIN:
                lv_obj_add_state(objects.config_curtain_btn, LV_STATE_CHECKED);
                break;
            case ACTIVE_CONFIG_PAGE_MODE:
                lv_obj_add_state(objects.config_mode_btn, LV_STATE_CHECKED);
                break;
            default:
                ESP_LOGE(TAG, "不, 不可能: %d", active_config_page);
                return;
        }
        lv_obj_add_flag(objects.page_air, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.config_table_header, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.config_table_footer, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.page_number, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.obj_container, LV_OBJ_FLAG_HIDDEN);

        current_page = 0;
        refresh_page();
    }
}

extern "C" void action_begin_rename_device(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_SHORT_CLICKED) {
        lv_obj_t *btn = lv_event_get_target(e);
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        current_rename_label = label;

        switch (active_config_page) {
            case ACTIVE_CONFIG_PAGE_LAMP:
                lv_obj_clear_flag(objects.lamp_name_selector, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.curtain_name_selector, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.mode_name_selector, LV_OBJ_FLAG_HIDDEN);
                return;
            case ACTIVE_CONFIG_PAGE_CURTAIN:
                lv_obj_add_flag(objects.lamp_name_selector, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(objects.curtain_name_selector, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.mode_name_selector, LV_OBJ_FLAG_HIDDEN);
                return;
            case ACTIVE_CONFIG_PAGE_MODE:
                lv_obj_add_flag(objects.lamp_name_selector, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.curtain_name_selector, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(objects.mode_name_selector, LV_OBJ_FLAG_HIDDEN);
                return;
            default:
                ESP_LOGE(TAG, "不可能的: %d", active_config_page);
                return;
        }
    }
}

extern "C" void action_rename_device(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_PRESSED) {
        lv_obj_t *btn = lv_event_get_target(e);

        lv_obj_t *label = lv_obj_get_child(btn, 0);
        const char *text = lv_label_get_text(label);
        if (current_rename_label == nullptr) {
            ESP_LOGE(TAG, "current_rename_label  == nullptr");
            return;
        }
        lv_label_set_text(current_rename_label, text);

        lv_obj_add_flag(objects.lamp_name_selector, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.curtain_name_selector, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.mode_name_selector, LV_OBJ_FLAG_HIDDEN);
    }
}

extern "C" void action_exit_rename_device(lv_event_t *e) {
    lv_obj_add_flag(objects.lamp_name_selector, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.curtain_name_selector, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.mode_name_selector, LV_OBJ_FLAG_HIDDEN);
}

static std::vector<lv_obj_t*> &get_current_vector() {
    switch(active_config_page) {
        case ACTIVE_CONFIG_PAGE_LAMP:    return lamp_objs;
        case ACTIVE_CONFIG_PAGE_CURTAIN: return curtain_objs;
        case ACTIVE_CONFIG_PAGE_MODE:    return mode_objs;
        default:
            ESP_LOGE(TAG, "不应该的配置页: %d", active_config_page);
            static std::vector<lv_obj_t *> dummy;
            return dummy;
    }
}

static void refresh_page() {
    if (active_config_page != ACTIVE_CONFIG_PAGE_LAMP &&
        active_config_page != ACTIVE_CONFIG_PAGE_CURTAIN &&
        active_config_page != ACTIVE_CONFIG_PAGE_MODE) {
        lv_obj_add_flag(objects.obj_container, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    // 全部隐藏
    for (lv_obj_t *obj : lamp_objs)    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    for (lv_obj_t *obj : curtain_objs) lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    for (lv_obj_t *obj : mode_objs)    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    
    // 根据当前页数, 显示对应数量的项目
    auto &items = get_current_vector();
    int total = items.size();
    int total_pages = (total + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    if (total_pages == 0) total_pages = 1;
    if (current_page >= total_pages) current_page = total_pages - 1; // 其实current_page是0的时候, 表示第一页; 一个是偏移一个是正常数字, 所以有奇怪的+1-1
    
    int start = current_page * ITEMS_PER_PAGE;
    for(int i = 0; i < ITEMS_PER_PAGE; ++i) {
        int idx = start + i;
        if(idx >= total) break;
        lv_obj_clear_flag(items[idx], LV_OBJ_FLAG_HIDDEN);
    }
    
    lv_obj_clear_flag(objects.obj_container, LV_OBJ_FLAG_HIDDEN);

    lv_label_set_text_fmt(objects.page_number, "%d/%d", current_page + 1, total_pages);

}

extern "C" void action_add_new_device(lv_event_t *e) {
    if (active_config_page != ACTIVE_CONFIG_PAGE_LAMP &&
        active_config_page != ACTIVE_CONFIG_PAGE_CURTAIN &&
        active_config_page != ACTIVE_CONFIG_PAGE_MODE) {
        lv_obj_add_flag(objects.obj_container, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    switch (active_config_page) {
        case ACTIVE_CONFIG_PAGE_LAMP:
            if (lamp_objs.size() >= MAX_LAMP_COUNT) return;
            break;
        case ACTIVE_CONFIG_PAGE_CURTAIN:
            if (curtain_objs.size() >= MAX_CURTAIN_COUNT) return;
            break;
        case ACTIVE_CONFIG_PAGE_MODE:
            if (mode_objs.size() >= MAX_MODE_COUNT) return;
            break;
        default:
            break;
    }

    lv_obj_t *item = create_device_item(objects.obj_container);
    // lv_obj_add_flag(item, LV_OBJ_FLAG_HIDDEN);
    // lv_obj_set_style_shadow_width(item, 0, LV_PART_MAIN);
    // lv_obj_set_style_radius(item, 0, LV_PART_MAIN);
    // lv_obj_set_style_border_width(item, 0, LV_PART_MAIN);
    
    auto &vec = get_current_vector();
    vec.push_back(item);
    // 添加新项目后固定跳转至最后一页, 因为那个肯定在最后一页啊
    int total_pages = (vec.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    current_page = total_pages - 1;

    refresh_page();
}

extern "C" void action_next_page(lv_event_t *e) {
    auto &vec = get_current_vector();
    int max_page = (vec.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    if(current_page < max_page - 1) {
        current_page++;
        refresh_page();
    }
}

extern "C" void action_prev_page(lv_event_t *e) {
    if(current_page > 0) {
        current_page--;
        refresh_page();
    }
}

extern "C" void action_delete_device(lv_event_t *e) {
    lv_obj_t *btn = lv_obj_get_parent(current_rename_label);
    lv_obj_t *root = lv_obj_get_parent(btn);

    auto &vec = get_current_vector();
    auto it = std::find(vec.begin(), vec.end(), root);
    if (it != vec.end()) vec.erase(it);

    lv_obj_del(root);

    action_exit_rename_device(nullptr);
    refresh_page();
}

lv_obj_t *create_device_item(lv_obj_t *parent_obj) {
    // 根对象（容器）
    lv_obj_t *obj = lv_obj_create(parent_obj);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 370, 70);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff606060), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 按钮（带有label）
    lv_obj_t *btn = lv_btn_create(obj);
    lv_obj_set_pos(btn, -6, -5);
    lv_obj_set_size(btn, 100, 50);
    lv_obj_add_event_cb(btn, action_begin_rename_device, LV_EVENT_ALL, nullptr);
    add_style_test(btn);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label = lv_label_create(btn);
    lv_obj_set_pos(label, 0, 0);
    lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(label, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label, "点此命名");

    // 第一个roller（16档）
    lv_obj_t *roller1 = lv_roller_create(obj);
    lv_obj_set_pos(roller1, 140, -16);
    lv_obj_set_size(roller1, 80, 70);
    lv_roller_set_options(roller1, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_style_border_width(roller1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(roller1, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(roller1, lv_color_hex(0xff2196f3), LV_PART_SELECTED | LV_STATE_DEFAULT);

    // 第二个roller（8档）
    lv_obj_t *roller2 = lv_roller_create(obj);
    lv_obj_set_pos(roller2, 262, -16);
    lv_obj_set_size(roller2, 80, 70);
    lv_roller_set_options(roller2, "0\n1\n2\n3\n4\n5\n6\n7", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_style_border_width(roller2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(roller2, &ui_font_ping_fang22, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    return obj;
}

ObjConfigInfo get_obj_config_info(const lv_obj_t* obj) {
    ObjConfigInfo info = {};

    if (!obj) return info;

    lv_obj_t* btn = lv_obj_get_child(obj, 0);
    if (!btn) {
        ESP_LOGE(TAG, "此obj没有索引为0的子对象");
        return info;
    }

    lv_obj_t* label = lv_obj_get_child(btn, 0);
    if (!label) {
        ESP_LOGE(TAG, "此btn没有索引为0的子对象");
        return info;
    }

    info.name = lv_label_get_text(label);

    lv_obj_t* roll1 = lv_obj_get_child(obj, 1);
    lv_obj_t* roll2 = lv_obj_get_child(obj, 2);
    if (!roll1 || !roll2) {
        ESP_LOGE(TAG, "此obj没有索引为1或2的子对象");
        return info;
    }

    if (roll1) info.panel_id = lv_roller_get_selected(roll1);
    if (roll2) info.button_id = lv_roller_get_selected(roll2);

    return info;
}