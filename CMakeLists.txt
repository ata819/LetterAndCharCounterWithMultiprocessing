cmake_minimum_required(VERSION 3.16)
project(prog1 C)

set(CMAKE_C_STANDARD 99)

add_executable(prog1 main.c mulproc.c)