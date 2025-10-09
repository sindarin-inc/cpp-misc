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
        PRIV_REQUIRES spiram-cpp idflog
    )

    target_compile_options(${COMPONENT_TARGET} PUBLIC ${compile_options})

else()

    add_library(bmpimage STATIC
        ${SOURCES}
    )
    target_include_directories(bmpimage PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(bmpimage PRIVATE spiram-cpp idflog)

endif()
