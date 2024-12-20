cmake_minimum_required(VERSION 3.16)
project(hotel C)

set(CMAKE_C_STANDARD 90)
include_directories(include src/ui src/hotel)

add_executable(hotel src/main.c
        src/hotel/auth/login.c
        src/hotel/auth/login.h
        src/hotel/management/rooms.c
        src/hotel/management/rooms.h

        src/ui/menus/main.c
        src/ui/menus/main.h
        src/ui/menus/root.c
        src/ui/menus/root.h
        src/ui/menus/login.c
        src/ui/menus/login.h
        src/ui/menus/availability.c
        src/ui/menus/availability.h
        src/ui/menus/reservation.c
        src/ui/menus/reservation.h
        src/ui/ui.h


        include/libui/platform.c
        include/libui/platform.h
        include/libui/io.c
        include/libui/io.h
        include/libui/charcodes.h

        include/libdate.c
        include/libdate.h



)
