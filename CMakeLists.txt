cmake_minimum_required(VERSION 3.16)
project(hotel C)

set(CMAKE_C_STANDARD 90)
include_directories(include src/ui)

add_executable(hotel src/main.c
        include/auth/login.c
        include/auth/login.h
        include/libui/platform.c
        include/libui/platform.h
        include/libui/io.c
        include/libui/io.h
        include/libui/charcodes.h
        src/ui/menus/main.c
        src/ui/menus/main.h
        src/ui/menus/root.c
        src/ui/menus/root.h
        src/ui/menus/login.c
        src/ui/menus/login.h
        src/ui/ui.h
)
