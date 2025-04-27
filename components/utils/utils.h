#pragma once
#include <functional>

enum class DeviceType : uint8_t {
    Lamp = 0,
    Curtain = 1,
    Mode = 2
};

struct DeviceConfigPacked {
    uint8_t type;
    uint8_t panel_id;
    uint8_t button_id;
    char name[32];
};


class MultiTrigger {
public:
    MultiTrigger(uint8_t needed = 5, uint32_t interval_ms = 500)
        : needed_count(needed), interval(interval_ms) {}

    void trigger(const std::function<void()>& action) {
        uint32_t now = lv_tick_get();

        if (now - last_ms > interval) {
            count = 0;
        }
        last_ms = now;

        count++;
        if (count >= needed_count) {
            count = 0;
            action();
        }
    }

private:
    uint8_t needed_count;
    uint32_t interval;
    uint8_t count = 0;
    uint32_t last_ms = 0;
};


template <typename T>
void lv_set_data(lv_obj_t *obj, const T &data) {
    static_assert(std::is_copy_constructible<T>::value, "user_data type must be copyable");
    T *ptr = new T(data);
    lv_obj_set_user_data(obj, static_cast<void *>(ptr));
}

// 获取 user_data（返回指针，注意判空）
template <typename T>
T *lv_get_data(lv_obj_t *obj) {
    return static_cast<T *>(lv_obj_get_user_data(obj));
}

// 删除 user_data（释放堆内存）
template <typename T>
void lv_clear_data(lv_obj_t *obj) {
    T *ptr = lv_get_data<T>(obj);
    delete ptr;
    lv_obj_set_user_data(obj, nullptr);
}

// 修改 user_data（更新数据）
template <typename T>
bool lv_update_data(lv_obj_t *obj, const T &new_data) {
    T *ptr = lv_get_data<T>(obj);
    if (ptr) {
        *ptr = new_data;
        return true;
    } else {
        // 不存在则新建
        lv_set_data<T>(obj, new_data);
        return false;
    }
}