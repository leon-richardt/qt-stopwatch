cmake_minimum_required(VERSION 3.1.0)

project(stopwatch-ctl)

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

find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_executable(stopwatch-ctl
    src/main.cpp
)

target_compile_options(stopwatch-ctl PUBLIC "$<$<CONFIG:RELEASE>:-O3>")

target_link_libraries(stopwatch-ctl Qt5::Core Qt5::Network)
