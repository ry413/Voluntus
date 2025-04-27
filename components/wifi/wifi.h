#pragma once

void start_wifi_network();
bool network_is_ready();
void init_reconnect_timer();
bool save_wifi_credentials(const char* ssid, const char* pass);