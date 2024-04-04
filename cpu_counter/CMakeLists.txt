cmake_minimum_required(VERSION 3.26)
project(cpu_counter)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpu_counter main.cpp)

target_link_libraries(cpu_counter PRIVATE pdh)