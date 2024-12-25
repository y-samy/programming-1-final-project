cmake_minimum_required(VERSION 3.16)
project(hotel C)

set(CMAKE_C_STANDARD 90)
include_directories(include src/ui src/hotel)

add_executable(hotel src/main.c
        src/hotel/login.c
        src/hotel/login.h
        src/hotel/management.c
        src/hotel/management.h

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
        src/ui/menus/check_in.c
        src/ui/menus/check_in.h
        src/ui/menus/status.h
        src/ui/menus/cancel_reservation.c
        src/ui/menus/cancel_reservation.h
        src/ui/menus/view_customer_details.c
        src/ui/menus/view_customer_details.h
        src/ui/menus/query.h
        src/ui/menus/query.c
        src/ui/ui.h


        include/libui/platform.c
        include/libui/platform.h
        include/libui/io.c
        include/libui/io.h
        include/libui/charcodes.h

        include/libdate.c
        include/libdate.h

        include/libparse.c
        include/libparse.h
        src/ui/menus/edit_reservation.c
        src/ui/menus/edit_reservation.h
        src/ui/menus/check_out.c
        src/ui/menus/check_out.h
        src/ui/menus/reservation_report.c
        src/ui/menus/reservation_report.h


)

target_link_libraries(hotel)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|Intel")
    target_link_libraries(hotel m)
endif ()