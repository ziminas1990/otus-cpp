cmake_minimum_required(VERSION 3.2)

set(TASK_ID 1820)

project(timus-${TASK_ID})

add_executable(timus-${TASK_ID} main.cpp)
set_target_properties(timus-${TASK_ID} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
