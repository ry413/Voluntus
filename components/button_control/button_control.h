#pragma once

#include <stdint.h>
#include <vector>
#include "lvgl.h"
#include "config_page.h"

#define PANEL_COUNT 16
#define BUTTON_COUNT 8      // 一个面板里最多有8个按钮, 毋庸置疑

extern std::vector<lv_obj_t *> lamp_btns;
extern std::vector<lv_obj_t *> curtain_btns;
extern std::vector<lv_obj_t *> mode_btns;

class Panel {
public:
    void set_button_state(uint8_t button_id, bool state);
    void report_panel_state();
    void discard_state();
    void update_lights(uint8_t btn_lights);
    
    void set_panel_id(uint8_t id) { this->id = id;}
private:
    uint8_t id;
    uint8_t curr_btn_press_states = 0xFF;
    uint8_t curr_btn_light_states = 0x00;

    bool buttons_press[BUTTON_COUNT] = {false};     // true表示按钮按下, false为释放
    bool buttons_light[BUTTON_COUNT] = {false};     // true表示当前按钮指示灯亮, false为灭
    std::vector<uint8_t> state_queue;               // 此面板储存的待上班按键状态
    
};

class PanelManager {
public:
    static PanelManager& getInstance() {
        static PanelManager instance;
        return instance;
    }

    void action_button(ObjConfigInfo *info, bool is_press);
    void discard_all_state();
    void report_all_state();
    void update_lights(uint8_t panel_id, uint8_t btn_lights);

private:
    Panel panels[PANEL_COUNT];

    PanelManager() {
        for (int i = 0; i < PANEL_COUNT; i++) {
            panels[i].set_panel_id(i);
        }
    }
    ~PanelManager() = default;

    PanelManager(const PanelManager&) = delete;
    PanelManager& operator=(const PanelManager&) = delete;
};