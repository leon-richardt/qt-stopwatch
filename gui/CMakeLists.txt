cmake_minimum_required(VERSION 3.1.0)

project(stopwatch)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

add_executable(stopwatch
    src/main.cpp
    src/IpcServer.cpp
    src/StopwatchWidget.cpp
    src/UpdateWorker.cpp
)

target_compile_options(stopwatch PUBLIC "$<$<CONFIG:RELEASE>:-O3>")
target_compile_options(stopwatch PUBLIC "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>")

target_link_libraries(stopwatch Qt5::Core Qt5::Widgets Qt5::Network)
