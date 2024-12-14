cmake_minimum_required(VERSION 3.16)
project(hotel C)

set(CMAKE_C_STANDARD 90)

add_executable(hotel src/main.c
        src/login.c
        src/login.h
        src/ui.c
        src/ui.h
        src/platform.c
        src/platform.h
        src/libui.c
        src/libui.h)
