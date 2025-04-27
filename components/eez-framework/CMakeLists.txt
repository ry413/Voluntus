if(ESP_PLATFORM)
    get_filename_component(dir ${CMAKE_CURRENT_LIST_FILE} PATH)
    file(GLOB_RECURSE app_sources ${dir}/src/eez/*.c* ${dir}/src/eez/*.cpp)

    idf_component_register(
        SRCS ${app_sources}
        INCLUDE_DIRS "src" "src/eez/libs/agg"
        PRIV_REQUIRES lvgl esp_timer
    )
    target_compile_definitions(${COMPONENT_LIB} PRIVATE EEZ_FOR_LVGL EEZ_PLATFORM_ESP32)
else()
    cmake_minimum_required(VERSION 3.12)

    include_directories(
        ./src
        ./src/eez/libs/agg
    )

    file(GLOB_RECURSE SOURCES
        ./src/eez/*.cpp
        ./src/eez/*.c
    )

    ADD_LIBRARY(eez-framework STATIC ${SOURCES})

    target_include_directories(eez-framework SYSTEM PUBLIC ./src ./src/eez/libs/agg)
endif()
