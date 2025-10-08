cmake_minimum_required(VERSION 3.16)

project(defer-desktop)

# Build the library from the repository root as a subdirectory
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../.. defer)

add_executable(example
    main.cpp
)

target_link_libraries(example PUBLIC defer)
