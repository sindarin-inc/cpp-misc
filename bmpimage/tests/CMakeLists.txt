cmake_minimum_required(VERSION 3.20)

project(bmpimage_tests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(REPO_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

enable_testing()

add_subdirectory(${REPO_ROOT}/vendor/Catch2 ${CMAKE_CURRENT_BINARY_DIR}/Catch2)
add_subdirectory(${REPO_ROOT}/spiram-cpp ${CMAKE_CURRENT_BINARY_DIR}/spiram-cpp)
add_subdirectory(${REPO_ROOT}/idflog ${CMAKE_CURRENT_BINARY_DIR}/idflog)
add_subdirectory(${REPO_ROOT}/imagetest ${CMAKE_CURRENT_BINARY_DIR}/imagetest)
add_subdirectory(${REPO_ROOT}/bmpimage ${CMAKE_CURRENT_BINARY_DIR}/bmpimage)

add_executable(tests_bmpimage
    ${CMAKE_CURRENT_LIST_DIR}/TestBMPImage.cpp
)

target_compile_definitions(tests_bmpimage PRIVATE TESTS_DIR="${CMAKE_CURRENT_LIST_DIR}")
find_package(PNG REQUIRED)
target_link_libraries(tests_bmpimage PRIVATE catch2 imagetest bmpimage)

add_test(NAME bmpimage COMMAND tests_bmpimage)
