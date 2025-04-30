idf_component_register(SRCS "rs485.cpp"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES config_page time_sync air driver button_control ui idle_manager)
