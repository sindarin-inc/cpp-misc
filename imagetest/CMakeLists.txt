cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(imagetest STATIC
    ${SOURCES}
)

target_include_directories(imagetest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(PNG REQUIRED)

target_link_libraries(imagetest PRIVATE PNG::PNG)
