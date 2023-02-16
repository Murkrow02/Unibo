cmake_minimum_required (VERSION 3.5)
project(Pandos+ VERSION 0.1 LANGUAGES C ASM)
enable_testing()


# Cross-compile for the target environment by default
# Can be disabled to compile with the system's `cc` and run unit tests locally
option(CROSS_COMPILE "Cross compile for the MIPS architecture" ON)
option(DEBUG "Enable GDB debug flags" OFF)
set(XT_PRG_PREFIX "mipsel-linux-gnu-" CACHE STRING "GCC cross compiler prefix")

# Set hashtable header path
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I /usr/src/linux-headers-5.19.0-31/include/linux/hashtable.h")

find_program(MIPSEL_CC ${XT_PRG_PREFIX}gcc REQUIRED)
find_program(MIPSEL_LD ${XT_PRG_PREFIX}ld REQUIRED)

# Locate the UMPS3 header/obj files
if(NOT DEFINED UMPS3_DIR_PREFIX)
    set(UMPS3_DIR_PREFIX /usr)
    if(EXISTS /usr/local/bin/umps3)
        set(UMPS3_DIR_PREFIX /usr/local)
    endif()
endif()

set(CFLAGS_LANG -pedantic -ffreestanding -Wall -ansi -std=gnu99)
if(CROSS_COMPILE)
    # Compile the kernel binary to a bare metal executable with these flags
    set(CFLAGS_MIPS -mips1 -mabi=32 -mno-gpopt -EL -G0 -O0 -mno-abicalls -fno-pic -mfp32)
    set(CFLAGS_ALL ${CMAKE_C_FLAGS} ${CFLAGS_LANG} ${CFLAGS_MIPS})
    set(LDFLAGS_ALL ${LDFLAGS_ALL} -G0 -nostdlib -T ${UMPS3_DIR_PREFIX}/share/umps3/umpscore.ldscript -melf32ltsmip)
endif()

# The library code for all project phases, as a subproject
add_subdirectory(os)

if(CROSS_COMPILE)
    add_subdirectory(phase1)
endif()
