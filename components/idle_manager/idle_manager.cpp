#include "esp_log.h"
#include "idle_manager.h"
#include "lvgl.h"
#include "screens.h"
#include "utils.h"
#include "backlight.h"

#define TAG "IDLE_MANAGER"

static lv_timer_t *idle_timer = nullptr;    // 一次性无操作定时器
void show_random_4_tip(lv_obj_t *container);

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
        // 主界面则进入待机界面
        else {
            ESP_LOGI(TAG, "无操作, 进入待机界面");
            lv_obj_clear_flag(objects.idle_overlay, LV_OBJ_FLAG_HIDDEN);
            show_random_4_tip(objects.idle_screen_container);
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

// 用于在待机界面随机显示四个提示
void show_random_4_tip(lv_obj_t *container) {
    uint32_t child_count = lv_obj_get_child_cnt(container);
    if (child_count <= 4) {
        ESP_LOGE(TAG, "这个怎么样也不可能");
        return;
    }

    // 创建索引数组
    uint32_t indices[child_count];
    for (uint32_t i = 0; i < child_count; i++) {
        indices[i] = i;
    }

    // 洗牌算法：Fisher–Yates shuffle
    for (uint32_t i = child_count - 1; i > 0; i--) {
        uint32_t j = rand() % (i + 1);
        uint32_t tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    // 显示前4个，隐藏其余
    for (uint32_t i = 0; i < child_count; i++) {
        lv_obj_t *child = lv_obj_get_child(container, indices[i]);
        if (i < 4) {
            lv_obj_clear_flag(child, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(child, LV_OBJ_FLAG_HIDDEN);
        }
    }
}