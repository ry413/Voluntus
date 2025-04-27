#pragma once
#include "vars.h"

void init_air_commit_timer();

AIR_MODE bitsToMode(uint8_t mode_bits);
AIR_FAN_SPEED bitsToFanSpeed(uint8_t fan_speed_bits);
uint8_t modeToBits(AIR_MODE mode);
uint8_t fanSpeedToBits(AIR_FAN_SPEED fan_speed);    