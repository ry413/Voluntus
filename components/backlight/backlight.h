#pragma once

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_PIN                1
#define LEDC_RESOLUTION         LEDC_TIMER_8_BIT
#define MAX_BACKLIGHT_DUTY      127

void init_backlight();
void open_backlight();
void close_backlight();