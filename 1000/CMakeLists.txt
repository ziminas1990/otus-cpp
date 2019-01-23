cmake_minimum_required(VERSION 3.2)

project(timus-1000)

add_executable(timus-1000 main.cpp)
set_target_properties(timus-1000 PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
