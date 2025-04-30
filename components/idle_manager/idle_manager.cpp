#include "esp_log.h"
#include "idle_manager.h"
#include "lvgl.h"
#include "screens.h"
#include "utils.h"

#define TAG "IDLE_MANAGER"

static lv_timer_t *idle_timer = nullptr;    // 一次性无操作定时器
// static lv_timer_t *fadeout_timer = nullptr; // 熄屏逻辑中使用的, 用于管理渐隐遮罩层

// 无操作定时器回调
static void on_idle_timeout(lv_timer_t * t) {
    // 立即暂停定时器，避免重复触发
    lv_timer_pause(t);

    lv_async_call([](void *param) {
        // 非主界面则返回主界面
        if (lv_scr_act() != objects.main) {
            ESP_LOGI(TAG, "无操作, 返回主界面");
            lv_scr_load(objects.main);
            reset_idle_monitor();
        }
        // 主界面则熄屏
        else {
            ESP_LOGI(TAG, "无操作, 熄屏");
            lv_obj_clear_flag(objects.idle_overlay, LV_OBJ_FLAG_HIDDEN);
        }
    }, NULL);
}

// 创建无操作定时器
void init_idle_monitor(uint32_t timeout_ms) {
    if (idle_timer) {
        lv_timer_del(idle_timer);
    }

    idle_timer = lv_timer_create(on_idle_timeout, timeout_ms, NULL);
}

// 重置无操作定时器, 给全局触摸事件调用
void reset_idle_monitor() {
    if (idle_timer) {
        lv_timer_reset(idle_timer);
        lv_timer_resume(idle_timer);
    }
}

// void del_fadeout_timer() {
//     if (fadeout_timer) {
//         lv_timer_del(fadeout_timer);
//         fadeout_timer = nullptr;
//     }
// }