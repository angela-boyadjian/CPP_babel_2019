# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build

# Include any dependencies generated for this target.
include CMakeFiles/client_bin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client_bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_bin.dir/flags.make

CMakeFiles/client_bin.dir/srcs/client/main.cpp.o: CMakeFiles/client_bin.dir/flags.make
CMakeFiles/client_bin.dir/srcs/client/main.cpp.o: ../srcs/client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client_bin.dir/srcs/client/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_bin.dir/srcs/client/main.cpp.o -c /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/srcs/client/main.cpp

CMakeFiles/client_bin.dir/srcs/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_bin.dir/srcs/client/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/srcs/client/main.cpp > CMakeFiles/client_bin.dir/srcs/client/main.cpp.i

CMakeFiles/client_bin.dir/srcs/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_bin.dir/srcs/client/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/srcs/client/main.cpp -o CMakeFiles/client_bin.dir/srcs/client/main.cpp.s

CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.o: CMakeFiles/client_bin.dir/flags.make
CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.o: ../srcs/network/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.o -c /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/srcs/network/Socket.cpp

CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/srcs/network/Socket.cpp > CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.i

CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/srcs/network/Socket.cpp -o CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.s

# Object files for target client_bin
client_bin_OBJECTS = \
"CMakeFiles/client_bin.dir/srcs/client/main.cpp.o" \
"CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.o"

# External object files for target client_bin
client_bin_EXTERNAL_OBJECTS =

bin/client_bin: CMakeFiles/client_bin.dir/srcs/client/main.cpp.o
bin/client_bin: CMakeFiles/client_bin.dir/srcs/network/Socket.cpp.o
bin/client_bin: CMakeFiles/client_bin.dir/build.make
bin/client_bin: CMakeFiles/client_bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/client_bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_bin.dir/build: bin/client_bin

.PHONY : CMakeFiles/client_bin.dir/build

CMakeFiles/client_bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_bin.dir/clean

CMakeFiles/client_bin.dir/depend:
	cd /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019 /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019 /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build /Users/Angela/Documents/programming/epitech/Tek3/CPP_babel_2019/build/CMakeFiles/client_bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_bin.dir/depend
