cmake_minimum_required(VERSION 3.24)
project(phase1_files C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(phase1_files
        container_of.h
        hash.h
        hashtable.h
        hashtable_api.h
        list.h
        log2.h
        p1test.c
        pandos_const.h
        pandos_types.h
        types.h pcb_utils.c ash_utils.h ash_utils.c ns_utils.h ns_utils.c)
