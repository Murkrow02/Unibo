# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build"

# Include any dependencies generated for this target.
include os/CMakeFiles/libumps.dir/depend.make

# Include the progress variables for this target.
include os/CMakeFiles/libumps.dir/progress.make

# Include the compile flags for this target's objects.
include os/CMakeFiles/libumps.dir/flags.make

os/CMakeFiles/libumps.dir/usr/share/umps3/libumps.S.o: os/CMakeFiles/libumps.dir/flags.make
os/CMakeFiles/libumps.dir/usr/share/umps3/libumps.S.o: /usr/share/umps3/libumps.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object os/CMakeFiles/libumps.dir/usr/share/umps3/libumps.S.o"
	cd "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/os" && /usr/bin/mipsel-linux-gnu-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/libumps.dir/usr/share/umps3/libumps.S.o -c /usr/share/umps3/libumps.S

# Object files for target libumps
libumps_OBJECTS = \
"CMakeFiles/libumps.dir/usr/share/umps3/libumps.S.o"

# External object files for target libumps
libumps_EXTERNAL_OBJECTS =

os/liblibumps.a: os/CMakeFiles/libumps.dir/usr/share/umps3/libumps.S.o
os/liblibumps.a: os/CMakeFiles/libumps.dir/build.make
os/liblibumps.a: os/CMakeFiles/libumps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking ASM static library liblibumps.a"
	cd "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/os" && $(CMAKE_COMMAND) -P CMakeFiles/libumps.dir/cmake_clean_target.cmake
	cd "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/os" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libumps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
os/CMakeFiles/libumps.dir/build: os/liblibumps.a

.PHONY : os/CMakeFiles/libumps.dir/build

os/CMakeFiles/libumps.dir/clean:
	cd "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/os" && $(CMAKE_COMMAND) -P CMakeFiles/libumps.dir/cmake_clean.cmake
.PHONY : os/CMakeFiles/libumps.dir/clean

os/CMakeFiles/libumps.dir/depend:
	cd "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+" "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/os" "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build" "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/os" "/media/psf/Unibo/Secondo Anno/Sistemi Operativi/panda+/build/os/CMakeFiles/libumps.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : os/CMakeFiles/libumps.dir/depend
