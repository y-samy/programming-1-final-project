cmake_minimum_required(VERSION 3.16)
project(hotel C)

set(CMAKE_C_STANDARD 90)
include_directories(lib src/auth)

add_executable(hotel src/main.c
        src/auth/login.c
        src/auth/login.h
        src/ui.c
        src/ui.h
        lib/libui/platform.c
        lib/libui/platform.h
        lib/libui/io.c
        lib/libui/io.h
        lib/libui/charcodes.h
        src/ui/main_menu.c
        src/ui/main_menu.h
        src/ui/root_menu.c
        src/ui/root_menu.h
        src/ui/status_codes.h)
