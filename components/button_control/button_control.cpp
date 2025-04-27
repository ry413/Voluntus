#include "button_control.h"
#include "esp_log.h"
#include "actions.h"
#include <vector>
#include "screens.h"
#include "config_page.h"
#include "utils.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include <stdio.h>
#include "rs485.h"

#define TAG "BUTTON_CONTROL"

bool panel_timeout[PANEL_COUNT];

// btns都是固定长度不可变的结构, 就是说整个生命周期里都固定存在着那么多按钮
std::vector<lv_obj_t *> lamp_btns;
std::vector<lv_obj_t *> curtain_btns;
std::vector<lv_obj_t *> mode_btns;

extern "C" void action_btn_touch(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    auto info = lv_get_data<ObjConfigInfo>(btn);

    if (lv_event_get_code(e) == LV_EVENT_PRESSED) {
        PanelManager::getInstance().action_button(info, true);

    } else if (lv_event_get_code(e) == LV_EVENT_RELEASED) {
        PanelManager::getInstance().action_button(info, false);
    }
}

void PanelManager::action_button(ObjConfigInfo *info, bool is_press) {
    panels[info->panel_id].set_button_state(info->button_id, is_press);
}

// 上报所有面板储存的状态
void PanelManager::report_all_state() {
    for (Panel &panel : panels) {
        panel.report_panel_state();
    }
}

// 洗白所有面板
void PanelManager::discard_all_state() {
    ESP_LOGI(TAG, "丢弃所有面板状态");
    for (Panel &panel : panels) {
        panel.discard_state();
    }
}

void PanelManager::update_lights(uint8_t panel_id, uint8_t lights_byte) {
    if (panel_id > PANEL_COUNT) {
        ESP_LOGE(TAG, "不存在的panel_id: %d", panel_id);
        return;
    }
    panels[panel_id].update_lights(lights_byte);
}

// 这个方法绝对只应该被"用户操作按键"作为扳机, buttons_press也是
void Panel::set_button_state(uint8_t button_id, bool state) {
    if (state) {
        // 按钮“按下” → 对应位清为 0
        curr_btn_press_states &= ~(1 << button_id);
    } else {
        // 按钮“松开” → 对应位设为 1
        curr_btn_press_states |= (1 << button_id);
    }
    ESP_LOGI(TAG, "state: 0x%02X 0x%02X", curr_btn_press_states, curr_btn_light_states);
    state_queue.push_back(curr_btn_press_states);
}

void Panel::report_panel_state() {
    if (state_queue.empty()) return;

    for (uint8_t state : state_queue) {
        sendRS485CMD(SWITCH_REPORT, 0x00, id, state, curr_btn_light_states);
    }
    discard_state();
}

void Panel::update_lights(uint8_t lights_byte) {
    // 更新bits
    curr_btn_light_states = lights_byte;
    
    // 遍历所有lamp
    for (int i = 0; i < lamp_objs.size(); i++) {
        lv_obj_t *lamp_btn = lamp_btns[i];
        ObjConfigInfo *info = lv_get_data<ObjConfigInfo>(lamp_btn);
        if (!info) {
            ESP_LOGE(TAG, "lamp没有ObjConfigInfo");
            continue;
        }

        // 如果当前obj所属此panel
        if (info->panel_id == this->id) {
            // 将对应位(即id)的状态拿来更新UI
            if (((curr_btn_light_states >> info->button_id) & 0x01) == 0x01) {
                lv_async_call([](void *param) {
                    lv_obj_t *btn = static_cast<lv_obj_t *>(param);
                    if (!lv_obj_has_state(btn, LV_STATE_CHECKED))
                        lv_obj_add_state(btn, LV_STATE_CHECKED);
                }, lamp_btn);
            } else {
                lv_async_call([](void *param) {
                    lv_obj_t *btn = static_cast<lv_obj_t *>(param);
                    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
                        lv_obj_clear_state(btn, LV_STATE_CHECKED);
                }, lamp_btn);
            }
        }
    }

    // curtain
    for (int i = 0; i < curtain_objs.size(); i++) {
        lv_obj_t *curtain_btn = curtain_btns[i];
        ObjConfigInfo *info = lv_get_data<ObjConfigInfo>(curtain_btn);
        if (!info) {
            ESP_LOGE(TAG, "curtain没有ObjConfigInfo");
            continue;
        }

        if (info->panel_id == this->id) {
            if (((curr_btn_light_states >> info->button_id) & 0x01) == 0x01) {
                lv_async_call([](void *param) {
                    lv_obj_t *btn = static_cast<lv_obj_t *>(param);
                    if (!lv_obj_has_state(btn, LV_STATE_CHECKED))
                        lv_obj_add_state(btn, LV_STATE_CHECKED);
                }, curtain_btn);
            } else {
                lv_async_call([](void *param) {
                    lv_obj_t *btn = static_cast<lv_obj_t *>(param);
                    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
                        lv_obj_clear_state(btn, LV_STATE_CHECKED);
                }, curtain_btn);
            }
        }
    }

    // mode
    for (int i = 0; i < mode_objs.size(); i++) {
        lv_obj_t *mode_btn = mode_btns[i];
        ObjConfigInfo *info = lv_get_data<ObjConfigInfo>(mode_btn);
        if (!info) {
            ESP_LOGE(TAG, "mode没有ObjConfigInfo");
            continue;
        }

        if (info->panel_id == this->id) {
            if (((curr_btn_light_states >> info->button_id) & 0x01) == 0x01) {
                lv_async_call([](void *param) {
                    lv_obj_t *btn = static_cast<lv_obj_t *>(param);
                    if (!lv_obj_has_state(btn, LV_STATE_CHECKED))
                        lv_obj_add_state(btn, LV_STATE_CHECKED);
                }, mode_btn);
            } else {
                lv_async_call([](void *param) {
                    lv_obj_t *btn = static_cast<lv_obj_t *>(param);
                    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
                        lv_obj_clear_state(btn, LV_STATE_CHECKED);
                }, mode_btn);
            }
        }
    }


}

void Panel::discard_state() {
    state_queue.clear();
}
