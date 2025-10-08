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
        REQUIRES spiram-cpp idflog miniz
    )

    target_compile_options(${COMPONENT_TARGET} PUBLIC ${compile_options})

else()

    add_library(unzipper STATIC
        ${SOURCES}
    )
    target_include_directories(unzipper PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    target_link_libraries(unzipper PRIVATE spiram-cpp idflog miniz)

endif()
