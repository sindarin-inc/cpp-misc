cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

if(DEFINED ESP_PLATFORM AND ESP_PLATFORM)
    set(compile_options
        -includesdkconfig.h
        -Wno-unknown-pragmas
    )

    idf_component_register(
        SRCS ${SOURCES}
        INCLUDE_DIRS "include"
        REQUIRES spiram-cpp
    )

    target_compile_options(${COMPONENT_TARGET} PUBLIC ${compile_options})

else()

    add_library(stringutil STATIC
        ${SOURCES}
    )
    target_include_directories(stringutil PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_compile_options(stringutil PRIVATE
        -Wno-unknown-pragmas
    )
    target_link_libraries(stringutil PRIVATE spiram-cpp)

endif()
