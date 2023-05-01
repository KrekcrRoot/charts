cmake_minimum_required(VERSION 3.25)
project(charts)

set(CMAKE_CXX_STANDARD 17)

include_directories(vendor)

add_executable(charts
        Source.cpp
        vendor/Charts.cpp
        vendor/Charts.h
        vendor/Log.cpp
        vendor/Log.h
        vendor/Window.cpp
        vendor/Window.h
        vendor/Config.h
        vendor/Camera.cpp
        vendor/Camera.h
        vendor/Equation.cpp
        vendor/Equation.h
        )

target_link_libraries(charts sfml-system sfml-window sfml-graphics)