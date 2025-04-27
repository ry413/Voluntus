#pragma once
#include <ctime>
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

    time_t now() {
        uint32_t elapsed_ms = lv_tick_elaps(last_tick_ms);
        return base_time + elapsed_ms / 1000;
    }

    void attach_label(lv_obj_t* label) {
        target_label = label;
        lv_timer_create(update_label_cb, 1000, this);
    }

    static void update_label_cb(lv_timer_t* timer) {
        auto* self = static_cast<ClockManager*>(timer->user_data);
        if (!self->target_label) return;

        time_t t = self->now();
        struct tm* tm_info = localtime(&t);
        if (tm_info) {
            static char buf[6];
            snprintf(buf, sizeof(buf), "%02d:%02d", tm_info->tm_hour, tm_info->tm_min);
            lv_label_set_text(self->target_label, buf);
        }
    }

private:
    ClockManager() = default;

    time_t base_time = 0;
    uint32_t last_tick_ms = 0;
    lv_obj_t* target_label = nullptr;
};
    