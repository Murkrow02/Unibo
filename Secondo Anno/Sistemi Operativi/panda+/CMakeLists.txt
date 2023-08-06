cmake_minimum_required (VERSION 3.5)
project(Pandos+ VERSION 0.1 LANGUAGES C ASM)


option(CROSS_COMPILE "Cross compile for the MIPS architecture" ON)
set(XT_PRG_PREFIX "mipsel-linux-gnu-" CACHE STRING "GCC cross compiler prefix")

# Set hashtable header path
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I /usr/src/linux-headers-5.19.0-31/include/linux/hashtable.h")

find_program(MIPSEL_CC ${XT_PRG_PREFIX}gcc REQUIRED)
find_program(MIPSEL_LD ${XT_PRG_PREFIX}ld REQUIRED)
if(NOT DEFINED UMPS3_DIR_PREFIX)
    set(UMPS3_DIR_PREFIX /usr)
    if(EXISTS /usr/local/bin/umps3)
        set(UMPS3_DIR_PREFIX /usr/local)
    endif()
endif()

set(CFLAGS_LANG -pedantic -ffreestanding -Wall -ansi -std=gnu99)

set(CFLAGS_MIPS -mips1 -mabi=32 -mno-gpopt -EL -G0 -O0 -mno-abicalls -fno-pic -mfp32)
set(CFLAGS_ALL ${CMAKE_C_FLAGS} ${CFLAGS_LANG} ${CFLAGS_MIPS})
set(LDFLAGS_ALL ${LDFLAGS_ALL} -G0 -nostdlib -T ${UMPS3_DIR_PREFIX}/share/umps3/umpscore.ldscript -melf32ltsmip)


add_subdirectory(os)
#add_subdirectory(phase1)
add_subdirectory(phase2)

