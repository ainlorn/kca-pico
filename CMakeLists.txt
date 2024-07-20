cmake_minimum_required(VERSION 3.30)

include(pico_sdk_import.cmake)

project(kca_pico CXX C ASM)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_subdirectory(src)
