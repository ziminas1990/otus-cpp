cmake_minimum_required(VERSION 3.2)

project(timus-2012)

add_executable(timus-2012 main.cpp)
set_target_properties(timus-2012 PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
