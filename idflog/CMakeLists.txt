cmake_minimum_required(VERSION 3.16)

if(DEFINED ESP_PLATFORM AND ESP_PLATFORM)
    set(compile_options
        -includesdkconfig.h
    )
    idf_component_register(
        INCLUDE_DIRS "include"
    )
else()
    add_library(idflog INTERFACE)
    target_include_directories(idflog INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
endif()
