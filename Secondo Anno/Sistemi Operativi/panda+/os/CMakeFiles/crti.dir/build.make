# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/murkrow/a

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/murkrow/a

# Include any dependencies generated for this target.
include os/CMakeFiles/crti.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include os/CMakeFiles/crti.dir/compiler_depend.make

# Include the progress variables for this target.
include os/CMakeFiles/crti.dir/progress.make

# Include the compile flags for this target's objects.
include os/CMakeFiles/crti.dir/flags.make

os/CMakeFiles/crti.dir/usr/share/umps3/crti.S.o: os/CMakeFiles/crti.dir/flags.make
os/CMakeFiles/crti.dir/usr/share/umps3/crti.S.o: /usr/share/umps3/crti.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/murkrow/a/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object os/CMakeFiles/crti.dir/usr/share/umps3/crti.S.o"
	cd /home/murkrow/a/os && /usr/bin/mipsel-linux-gnu-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/crti.dir/usr/share/umps3/crti.S.o -c /usr/share/umps3/crti.S

os/CMakeFiles/crti.dir/usr/share/umps3/crti.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/crti.dir/usr/share/umps3/crti.S.i"
	cd /home/murkrow/a/os && /usr/bin/mipsel-linux-gnu-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /usr/share/umps3/crti.S > CMakeFiles/crti.dir/usr/share/umps3/crti.S.i

os/CMakeFiles/crti.dir/usr/share/umps3/crti.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/crti.dir/usr/share/umps3/crti.S.s"
	cd /home/murkrow/a/os && /usr/bin/mipsel-linux-gnu-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /usr/share/umps3/crti.S -o CMakeFiles/crti.dir/usr/share/umps3/crti.S.s

# Object files for target crti
crti_OBJECTS = \
"CMakeFiles/crti.dir/usr/share/umps3/crti.S.o"

# External object files for target crti
crti_EXTERNAL_OBJECTS =

os/libcrti.a: os/CMakeFiles/crti.dir/usr/share/umps3/crti.S.o
os/libcrti.a: os/CMakeFiles/crti.dir/build.make
os/libcrti.a: os/CMakeFiles/crti.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/murkrow/a/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking ASM static library libcrti.a"
	cd /home/murkrow/a/os && $(CMAKE_COMMAND) -P CMakeFiles/crti.dir/cmake_clean_target.cmake
	cd /home/murkrow/a/os && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crti.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
os/CMakeFiles/crti.dir/build: os/libcrti.a
.PHONY : os/CMakeFiles/crti.dir/build

os/CMakeFiles/crti.dir/clean:
	cd /home/murkrow/a/os && $(CMAKE_COMMAND) -P CMakeFiles/crti.dir/cmake_clean.cmake
.PHONY : os/CMakeFiles/crti.dir/clean

os/CMakeFiles/crti.dir/depend:
	cd /home/murkrow/a && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/murkrow/a /home/murkrow/a/os /home/murkrow/a /home/murkrow/a/os /home/murkrow/a/os/CMakeFiles/crti.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : os/CMakeFiles/crti.dir/depend

