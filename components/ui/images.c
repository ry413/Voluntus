#include "images.h"

const ext_img_desc_t images[11] = {
    { "add", &img_add },
    { "dec", &img_dec },
    { "power", &img_power },
    { "mode_cooling", &img_mode_cooling },
    { "mode_hoting", &img_mode_hoting },
    { "mode_fan", &img_mode_fan },
    { "fan_high", &img_fan_high },
    { "fan_mid", &img_fan_mid },
    { "fan_low", &img_fan_low },
    { "fan_auto", &img_fan_auto },
    { "fan_speed_btn", &img_fan_speed_btn },
};
