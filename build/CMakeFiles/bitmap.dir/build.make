# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/software/software/CMake/3.16.4-GCCcore-9.3.0/bin/cmake

# The command to remove a file.
RM = /opt/software/software/CMake/3.16.4-GCCcore-9.3.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/gmwhitehair/Project3Github/CIS520_Pr3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/gmwhitehair/Project3Github/CIS520_Pr3/build

# Include any dependencies generated for this target.
include CMakeFiles/bitmap.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bitmap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bitmap.dir/flags.make

CMakeFiles/bitmap.dir/src/bitmap.c.o: CMakeFiles/bitmap.dir/flags.make
CMakeFiles/bitmap.dir/src/bitmap.c.o: ../src/bitmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/gmwhitehair/Project3Github/CIS520_Pr3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bitmap.dir/src/bitmap.c.o"
	/opt/software/software/GCCcore/9.3.0/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bitmap.dir/src/bitmap.c.o   -c /homes/gmwhitehair/Project3Github/CIS520_Pr3/src/bitmap.c

CMakeFiles/bitmap.dir/src/bitmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bitmap.dir/src/bitmap.c.i"
	/opt/software/software/GCCcore/9.3.0/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/gmwhitehair/Project3Github/CIS520_Pr3/src/bitmap.c > CMakeFiles/bitmap.dir/src/bitmap.c.i

CMakeFiles/bitmap.dir/src/bitmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bitmap.dir/src/bitmap.c.s"
	/opt/software/software/GCCcore/9.3.0/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/gmwhitehair/Project3Github/CIS520_Pr3/src/bitmap.c -o CMakeFiles/bitmap.dir/src/bitmap.c.s

# Object files for target bitmap
bitmap_OBJECTS = \
"CMakeFiles/bitmap.dir/src/bitmap.c.o"

# External object files for target bitmap
bitmap_EXTERNAL_OBJECTS =

libbitmap.a: CMakeFiles/bitmap.dir/src/bitmap.c.o
libbitmap.a: CMakeFiles/bitmap.dir/build.make
libbitmap.a: CMakeFiles/bitmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/gmwhitehair/Project3Github/CIS520_Pr3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libbitmap.a"
	$(CMAKE_COMMAND) -P CMakeFiles/bitmap.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bitmap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bitmap.dir/build: libbitmap.a

.PHONY : CMakeFiles/bitmap.dir/build

CMakeFiles/bitmap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bitmap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bitmap.dir/clean

CMakeFiles/bitmap.dir/depend:
	cd /homes/gmwhitehair/Project3Github/CIS520_Pr3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/gmwhitehair/Project3Github/CIS520_Pr3 /homes/gmwhitehair/Project3Github/CIS520_Pr3 /homes/gmwhitehair/Project3Github/CIS520_Pr3/build /homes/gmwhitehair/Project3Github/CIS520_Pr3/build /homes/gmwhitehair/Project3Github/CIS520_Pr3/build/CMakeFiles/bitmap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bitmap.dir/depend

