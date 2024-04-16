cmake_minimum_required(VERSION 3.10)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp
        ReadingMethods.cpp
        ReadingMethods.h
        SystemMetrics.cpp
        SystemMetrics.h
)

# Dodaj bibliotekę PDH
target_link_libraries(untitled1 PRIVATE pdh)
