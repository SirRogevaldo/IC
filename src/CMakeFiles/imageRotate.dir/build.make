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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joao/Desktop/4ºAno/IC/P/IC/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joao/Desktop/4ºAno/IC/P/IC/src

# Include any dependencies generated for this target.
include CMakeFiles/imageRotate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/imageRotate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imageRotate.dir/flags.make

CMakeFiles/imageRotate.dir/imageRotate.cpp.o: CMakeFiles/imageRotate.dir/flags.make
CMakeFiles/imageRotate.dir/imageRotate.cpp.o: imageRotate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joao/Desktop/4ºAno/IC/P/IC/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imageRotate.dir/imageRotate.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imageRotate.dir/imageRotate.cpp.o -c /home/joao/Desktop/4ºAno/IC/P/IC/src/imageRotate.cpp

CMakeFiles/imageRotate.dir/imageRotate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imageRotate.dir/imageRotate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joao/Desktop/4ºAno/IC/P/IC/src/imageRotate.cpp > CMakeFiles/imageRotate.dir/imageRotate.cpp.i

CMakeFiles/imageRotate.dir/imageRotate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imageRotate.dir/imageRotate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joao/Desktop/4ºAno/IC/P/IC/src/imageRotate.cpp -o CMakeFiles/imageRotate.dir/imageRotate.cpp.s

# Object files for target imageRotate
imageRotate_OBJECTS = \
"CMakeFiles/imageRotate.dir/imageRotate.cpp.o"

# External object files for target imageRotate
imageRotate_EXTERNAL_OBJECTS =

bin/imageRotate: CMakeFiles/imageRotate.dir/imageRotate.cpp.o
bin/imageRotate: CMakeFiles/imageRotate.dir/build.make
bin/imageRotate: /usr/local/lib/libopencv_gapi.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_highgui.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_ml.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_objdetect.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_photo.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_stitching.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_video.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_videoio.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_dnn.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_calib3d.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_features2d.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_flann.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_imgproc.so.4.6.0
bin/imageRotate: /usr/local/lib/libopencv_core.so.4.6.0
bin/imageRotate: CMakeFiles/imageRotate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joao/Desktop/4ºAno/IC/P/IC/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/imageRotate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imageRotate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imageRotate.dir/build: bin/imageRotate

.PHONY : CMakeFiles/imageRotate.dir/build

CMakeFiles/imageRotate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imageRotate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imageRotate.dir/clean

CMakeFiles/imageRotate.dir/depend:
	cd /home/joao/Desktop/4ºAno/IC/P/IC/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joao/Desktop/4ºAno/IC/P/IC/src /home/joao/Desktop/4ºAno/IC/P/IC/src /home/joao/Desktop/4ºAno/IC/P/IC/src /home/joao/Desktop/4ºAno/IC/P/IC/src /home/joao/Desktop/4ºAno/IC/P/IC/src/CMakeFiles/imageRotate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imageRotate.dir/depend
