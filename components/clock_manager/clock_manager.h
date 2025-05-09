#pragma once
#include <ctime>
#include <algorithm>
#include "lvgl.h"


class ClockManager {
public:
    static ClockManager& getInstance() {
        static ClockManager inst;
        return inst;
    }

    void init(time_t utc_time, int offset_seconds = 8 * 3600) {
        base_time = utc_time + offset_seconds;
        last_tick_ms = lv_tick_get();
    }

    time_t now() const {
        uint32_t elapsed_ms = lv_tick_elaps(last_tick_ms);
        return base_time + elapsed_ms / 1000;
    }

    void attach_label(lv_obj_t* label) {
        if (!label) return;

        // 避免重复添加
        if (std::find(target_labels.begin(), target_labels.end(), label) == target_labels.end()) {
            target_labels.push_back(label);
        }

        // 创建定时器（只创建一次）
        if (!timer) {
            timer = lv_timer_create(update_label_cb, 1000, this);
        }
    }

    static void update_label_cb(lv_timer_t* timer) {
        auto* self = static_cast<ClockManager*>(timer->user_data);
        if (self->target_labels.empty()) return;

        time_t t = self->now();
        struct tm* tm_info = localtime(&t);
        if (!tm_info) return;

        static char buf[6];
        snprintf(buf, sizeof(buf), "%02d %02d", tm_info->tm_hour, tm_info->tm_min);

        // 在主线程异步更新所有 label
        lv_async_call([](void* param) {
            auto* self = static_cast<ClockManager*>(param);
            for (auto* label : self->target_labels) {
                if (label) lv_label_set_text(label, buf);
            }
            
            // toggle待机界面的那个":"
            if (lv_obj_has_flag(objects.idle_screen_time_decora, LV_OBJ_FLAG_HIDDEN)) {
                lv_obj_clear_flag(objects.idle_screen_time_decora, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_add_flag(objects.idle_screen_time_decora, LV_OBJ_FLAG_HIDDEN);
            }
        }, self);
    }

private:
    ClockManager() = default;

    time_t base_time = 0;
    uint32_t last_tick_ms = 0;
    std::vector<lv_obj_t*> target_labels;
    lv_timer_t* timer = nullptr;
};