cmake_minimum_required(VERSION 3.22)

project(main VERSION 1.0)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BUILD_TYPE Debug)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(main ${SRC_FILES})

target_include_directories(main PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(main sfml-graphics sfml-window sfml-system sfml-audio)