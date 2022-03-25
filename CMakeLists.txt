cmake_minimum_required(VERSION 3.20)
project(my_cstring C)

set(CMAKE_C_STANDARD 99)

include_directories(string)

add_executable(example
        example.c
        string/str.c
        string/str.h)
