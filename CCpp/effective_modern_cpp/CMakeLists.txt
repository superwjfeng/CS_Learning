cmake_minimum_required(VERSION 3.0)

project(EFFECTIVEMODERNCPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLASG -fno-elide-constructors)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

add_executable(item7 item7.cc)
add_executable(item23 item23.cc)