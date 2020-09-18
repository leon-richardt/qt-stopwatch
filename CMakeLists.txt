cmake_minimum_required(VERSION 3.1.0)

project(stopwatch)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(stopwatch
    src/main.cpp
)

target_link_libraries(stopwatch Qt5::Widgets)
