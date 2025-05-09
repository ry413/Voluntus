#include "actions.h"
#include "vars.h"
#include "screens.h"
#include "config_page.h"
#include "button_control.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "utils.h"
#include "esp_system.h"
#include "idle_manager.h"

#define TAG "ACTIONS"

static void sync_configs_to_btns();
static void initialization();

extern "C" void action_scr_screen_to_main(lv_event_t *e) {
    lv_scr_load(objects.main);
}

extern "C" void action_scr_screen_to_lamp(lv_event_t *e) {
    lv_scr_load(objects.lamp_control);
}

extern "C" void action_scr_screen_to_curtain(lv_event_t *e) {
    lv_scr_load(objects.curtain_control);
}

extern "C" void action_scr_screen_to_config(lv_event_t *e) {
    static MultiTrigger enter_config_page_trigger;
    enter_config_page_trigger.trigger([]() {
        lv_scr_load(objects.config);
    });
}

extern "C" void action_main_screen_loaded_cb(lv_event_t *e) {
    initialization();
}

// 储存配置到nvs, 并应用
extern "C" void action_store_configs(lv_event_t *e) {
    std::vector<DeviceConfigPacked> all_devices;

    for (const lv_obj_t *obj : lamp_objs) {
        DeviceConfigPacked dev;
        dev.type = static_cast<uint8_t>(DeviceType::Lamp);
        ObjConfigInfo info = get_obj_config_info(obj);
        dev.panel_id = info.panel_id;
        dev.button_id = info.button_id;
        strncpy(dev.name, info.name, sizeof(dev.name));
        dev.name[sizeof(dev.name) - 1] = '\0';
        all_devices.push_back(dev);
    }
    
    for (const lv_obj_t *obj : curtain_objs) {
        DeviceConfigPacked dev;
        dev.type = static_cast<uint8_t>(DeviceType::Curtain);
        ObjConfigInfo info = get_obj_config_info(obj);
        dev.panel_id = info.panel_id;
        dev.button_id = info.button_id;
        strncpy(dev.name, info.name, sizeof(dev.name));
        dev.name[sizeof(dev.name) - 1] = '\0';
        all_devices.push_back(dev);
    }
    
    for (const lv_obj_t *obj : mode_objs) {
        DeviceConfigPacked dev;
        dev.type = static_cast<uint8_t>(DeviceType::Mode);
        ObjConfigInfo info = get_obj_config_info(obj);
        dev.panel_id = info.panel_id;
        dev.button_id = info.button_id;
        strncpy(dev.name, info.name, sizeof(dev.name));
        dev.name[sizeof(dev.name) - 1] = '\0';
        all_devices.push_back(dev);
    }

    nvs_handle_t handle;
    esp_err_t err = nvs_open("configs", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "打开 NVS 句柄失败: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_blob(handle, "device_cfg", all_devices.data(), all_devices.size() * sizeof(DeviceConfigPacked));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "写入 device_cfg 失败: %s", esp_err_to_name(err));
        nvs_close(handle);
        return;
    }
    nvs_commit(handle);
    nvs_close(handle);

    sync_configs_to_btns();
}

extern "C" void action_clean_all_configs(lv_event_t *e) {
    static MultiTrigger clean_all_configs_trigger;
    clean_all_configs_trigger.trigger([]() {
        nvs_handle_t handle;
        esp_err_t err = nvs_open("configs", NVS_READWRITE, &handle);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "打开 NVS 句柄失败: %s", esp_err_to_name(err));
            return;
        }

        err = nvs_erase_key(handle, "device_cfg");
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "device_cfg 清除成功");
            nvs_commit(handle);
        } else if (err == ESP_ERR_NVS_NOT_FOUND) {
            ESP_LOGW(TAG, "device_cfg 不存在，无需清除");
        } else {
            ESP_LOGE(TAG, "清除 device_cfg 失败: %s", esp_err_to_name(err));
        }

        nvs_close(handle);

        lamp_objs.clear();
        curtain_objs.clear();
        mode_objs.clear();
    });
}

static void load_configs() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open("configs", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "打开 NVS 句柄失败: %s", esp_err_to_name(err));
        return;
    }

    size_t size = 0;
    nvs_get_blob(handle, "device_cfg", nullptr, &size);
    ESP_LOGI(TAG, "device_cfg 长度: %d", size);

    if (size % sizeof(DeviceConfigPacked) == 0) {
        size_t count = size / sizeof(DeviceConfigPacked);
        DeviceConfigPacked loaded_devices[count];
        err = nvs_get_blob(handle, "device_cfg", loaded_devices, &size);

        if (err == ESP_OK) {
            for (int i = 0; i < count; i++) {
                auto &dev = loaded_devices[i];
                lv_obj_t *obj = create_device_item(objects.obj_container);
                lv_obj_t *btn = lv_obj_get_child(obj, 0);
                lv_obj_t *label = lv_obj_get_child(btn, 0);
                lv_label_set_text(label, dev.name);
                lv_obj_t *roll1 = lv_obj_get_child(obj, 1);
                lv_roller_set_selected(roll1, dev.panel_id, LV_ANIM_OFF);
                lv_obj_t *roll2 = lv_obj_get_child(obj, 2);
                lv_roller_set_selected(roll2, dev.button_id, LV_ANIM_OFF);
                
                switch (static_cast<DeviceType>(dev.type)) {
                    case DeviceType::Lamp:
                        lamp_objs.push_back(obj);
                        break;
                    case DeviceType::Curtain:
                        curtain_objs.push_back(obj);
                        break;
                    case DeviceType::Mode:
                        mode_objs.push_back(obj);
                        break;
                    default:
                        ESP_LOGW(TAG, "Unknown device type: %d", dev.type);
                        break;
                }
            }
        } else {
            ESP_LOGE(TAG, "读取 device_cfg 失败: %s", esp_err_to_name(err));
        }
    } else {
        ESP_LOGE(TAG, "device_cfg 长度错误");
    }

    nvs_close(handle);
}

// 同步配置页的所有配置到实际按钮上
static void sync_configs_to_btns() {
    for (int i = 0; i < MAX_LAMP_COUNT; i++) {
        if (i < lamp_objs.size()) {
            ObjConfigInfo info = get_obj_config_info(lamp_objs[i]);
            
            lv_obj_t *label = lv_obj_get_child(lamp_btns[i], 0);
            lv_label_set_text(label, info.name);
            
            lv_update_data<ObjConfigInfo>(lamp_btns[i], info);
            printf("已记录lamp %s %d %d\n", info.name, info.panel_id, info.button_id);

            lv_obj_clear_flag(lamp_btns[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(lamp_btns[i], LV_OBJ_FLAG_HIDDEN);
        }
    }

    for (int i = 0; i < MAX_CURTAIN_COUNT; i++) {
        if (i < curtain_objs.size()) {
            ObjConfigInfo info = get_obj_config_info(curtain_objs[i]);
            
            lv_obj_t *label = lv_obj_get_child(curtain_btns[i], 0);
            lv_label_set_text(label, info.name);
            
            lv_update_data<ObjConfigInfo>(curtain_btns[i], info);
            printf("已记录curtain %s %d %d\n", info.name, info.panel_id, info.button_id);

            lv_obj_clear_flag(curtain_btns[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(curtain_btns[i], LV_OBJ_FLAG_HIDDEN);
        }
    }

    for (int i = 0; i < MAX_MODE_COUNT; i++) {
        if (i < mode_objs.size()) {
            ObjConfigInfo info = get_obj_config_info(mode_objs[i]);

            lv_obj_t *label = lv_obj_get_child(mode_btns[i], 0);
            lv_label_set_text(label, info.name);
            
            lv_update_data<ObjConfigInfo>(mode_btns[i], info);
            printf("已记录mode %s %d %d\n", info.name, info.panel_id, info.button_id);

            lv_obj_clear_flag(mode_btns[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(mode_btns[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

// 在UI启动完毕后唯一的初始化
static void initialization() {
    static bool initialized = false;
    if (initialized) return;

    // 初始化这些固定结构
    if (lamp_btns.empty()) {
        lamp_btns.push_back(objects.lamp1);
        lamp_btns.push_back(objects.lamp2);
        lamp_btns.push_back(objects.lamp3);
        lamp_btns.push_back(objects.lamp4);
        lamp_btns.push_back(objects.lamp5);
        lamp_btns.push_back(objects.lamp6);
        lamp_btns.push_back(objects.lamp7);
        lamp_btns.push_back(objects.lamp8);
        lamp_btns.push_back(objects.lamp9);
        lamp_btns.push_back(objects.lamp10);
        lamp_btns.push_back(objects.lamp11);
        lamp_btns.push_back(objects.lamp12);
    }

    if (curtain_btns.empty()) {
        curtain_btns.push_back(objects.curtain1);
        curtain_btns.push_back(objects.curtain2);
        curtain_btns.push_back(objects.curtain3);
        curtain_btns.push_back(objects.curtain4);
        curtain_btns.push_back(objects.curtain5);
        curtain_btns.push_back(objects.curtain6);
    }

    if (mode_btns.empty()) {
        mode_btns.push_back(objects.mode1);
        mode_btns.push_back(objects.mode2);
        mode_btns.push_back(objects.mode3);
        mode_btns.push_back(objects.mode4);
        mode_btns.push_back(objects.mode5);
        mode_btns.push_back(objects.mode6);
    }
    lv_label_set_text(objects.version, VOLUNTUS_VERSION);
    load_configs();             // 加载nvs配置
    sync_configs_to_btns();     // 应用配置
    init_idle_monitor(30000);   // 启动待机定时器

    ESP_LOGI(TAG, "UI之后的初始化完成");
    initialized = true;
}

extern "C" void action_restart(lv_event_t *e) {
    static MultiTrigger restart_trigger;
    restart_trigger.trigger([]() {
        esp_restart();
    });
}

extern "C" void action_close_voice_response_popup(lv_event_t *e) {
    lv_obj_add_flag(objects.voice_response_popup, LV_OBJ_FLAG_HIDDEN);
}
