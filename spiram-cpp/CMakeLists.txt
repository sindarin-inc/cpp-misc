cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

if(DEFINED ESP_PLATFORM AND ESP_PLATFORM)
    set(compile_options
        -includesdkconfig.h
    )

    idf_component_register(
        SRCS ${SOURCES}
        INCLUDE_DIRS "include"
    )

    target_compile_options(${COMPONENT_TARGET} PUBLIC ${compile_options})
else()
    add_library(spiram-cpp STATIC
        ${SOURCES}
    )
    target_include_directories(spiram-cpp PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif()
