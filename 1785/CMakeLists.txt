cmake_minimum_required(VERSION 3.2)

project(timus-1785)

add_executable(timus-1785 main.cpp)
set_target_properties(timus-1785 PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
