idf_component_register(SRCS "rs485.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES config_page time_sync air driver lvgl button_control ui)
