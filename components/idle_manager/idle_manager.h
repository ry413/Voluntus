#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void init_idle_monitor(uint32_t timeout_ms);    // 无操作定时器
void reset_idle_monitor();                      // 重置无操作定时器
// void del_fadeout_timer();

#ifdef __cplusplus
}
#endif