#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_add;
extern const lv_img_dsc_t img_dec;
extern const lv_img_dsc_t img_power;
extern const lv_img_dsc_t img_mode_cooling;
extern const lv_img_dsc_t img_mode_hoting;
extern const lv_img_dsc_t img_mode_fan;
extern const lv_img_dsc_t img_fan_high;
extern const lv_img_dsc_t img_fan_mid;
extern const lv_img_dsc_t img_fan_low;
extern const lv_img_dsc_t img_fan_auto;
extern const lv_img_dsc_t img_fan_speed_btn;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[11];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/