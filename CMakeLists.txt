cmake_minimum_required(VERSION 3.29)
project(hotel C)

set(CMAKE_C_STANDARD 90)

add_executable(hotel src/main.c
        src/login.c
        src/login.h
        src/ui.c
        src/ui.h
        src/parse.c
        src/parse.h
        src/platform.c
        src/platform.h
        src/error.c
        src/error.h)
