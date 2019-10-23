cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Keypad)

add_executable(Keypad main.c)

target_link_libraries(Keypad PJ_RPI)
