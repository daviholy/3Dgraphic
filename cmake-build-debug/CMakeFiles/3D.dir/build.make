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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/CLionProjects/glfwTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/CLionProjects/glfwTest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/3D.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3D.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3D.dir/flags.make

CMakeFiles/3D.dir/3D.cpp.o: CMakeFiles/3D.dir/flags.make
CMakeFiles/3D.dir/3D.cpp.o: ../3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/CLionProjects/glfwTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3D.dir/3D.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3D.dir/3D.cpp.o -c /home/david/CLionProjects/glfwTest/3D.cpp

CMakeFiles/3D.dir/3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3D.dir/3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/CLionProjects/glfwTest/3D.cpp > CMakeFiles/3D.dir/3D.cpp.i

CMakeFiles/3D.dir/3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3D.dir/3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/CLionProjects/glfwTest/3D.cpp -o CMakeFiles/3D.dir/3D.cpp.s

CMakeFiles/3D.dir/glad.c.o: CMakeFiles/3D.dir/flags.make
CMakeFiles/3D.dir/glad.c.o: ../glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/CLionProjects/glfwTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/3D.dir/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/3D.dir/glad.c.o   -c /home/david/CLionProjects/glfwTest/glad.c

CMakeFiles/3D.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3D.dir/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/CLionProjects/glfwTest/glad.c > CMakeFiles/3D.dir/glad.c.i

CMakeFiles/3D.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3D.dir/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/CLionProjects/glfwTest/glad.c -o CMakeFiles/3D.dir/glad.c.s

CMakeFiles/3D.dir/Shader.cpp.o: CMakeFiles/3D.dir/flags.make
CMakeFiles/3D.dir/Shader.cpp.o: ../Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/CLionProjects/glfwTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/3D.dir/Shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3D.dir/Shader.cpp.o -c /home/david/CLionProjects/glfwTest/Shader.cpp

CMakeFiles/3D.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3D.dir/Shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/CLionProjects/glfwTest/Shader.cpp > CMakeFiles/3D.dir/Shader.cpp.i

CMakeFiles/3D.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3D.dir/Shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/CLionProjects/glfwTest/Shader.cpp -o CMakeFiles/3D.dir/Shader.cpp.s

CMakeFiles/3D.dir/Texture.cpp.o: CMakeFiles/3D.dir/flags.make
CMakeFiles/3D.dir/Texture.cpp.o: ../Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/CLionProjects/glfwTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/3D.dir/Texture.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3D.dir/Texture.cpp.o -c /home/david/CLionProjects/glfwTest/Texture.cpp

CMakeFiles/3D.dir/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3D.dir/Texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/CLionProjects/glfwTest/Texture.cpp > CMakeFiles/3D.dir/Texture.cpp.i

CMakeFiles/3D.dir/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3D.dir/Texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/CLionProjects/glfwTest/Texture.cpp -o CMakeFiles/3D.dir/Texture.cpp.s

# Object files for target 3D
3D_OBJECTS = \
"CMakeFiles/3D.dir/3D.cpp.o" \
"CMakeFiles/3D.dir/glad.c.o" \
"CMakeFiles/3D.dir/Shader.cpp.o" \
"CMakeFiles/3D.dir/Texture.cpp.o"

# External object files for target 3D
3D_EXTERNAL_OBJECTS =

3D: CMakeFiles/3D.dir/3D.cpp.o
3D: CMakeFiles/3D.dir/glad.c.o
3D: CMakeFiles/3D.dir/Shader.cpp.o
3D: CMakeFiles/3D.dir/Texture.cpp.o
3D: CMakeFiles/3D.dir/build.make
3D: ../dependencies/glfw3.a
3D: CMakeFiles/3D.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/CLionProjects/glfwTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable 3D"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3D.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3D.dir/build: 3D

.PHONY : CMakeFiles/3D.dir/build

CMakeFiles/3D.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3D.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3D.dir/clean

CMakeFiles/3D.dir/depend:
	cd /home/david/CLionProjects/glfwTest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/CLionProjects/glfwTest /home/david/CLionProjects/glfwTest /home/david/CLionProjects/glfwTest/cmake-build-debug /home/david/CLionProjects/glfwTest/cmake-build-debug /home/david/CLionProjects/glfwTest/cmake-build-debug/CMakeFiles/3D.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3D.dir/depend

