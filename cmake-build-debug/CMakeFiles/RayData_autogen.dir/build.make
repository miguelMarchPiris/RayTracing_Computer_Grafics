# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/desgarrador/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/desgarrador/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug

# Utility rule file for RayData_autogen.

# Include the progress variables for this target.
include CMakeFiles/RayData_autogen.dir/progress.make

CMakeFiles/RayData_autogen: qrc_resources.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target RayData"
	/home/desgarrador/clion-2019.3.4/bin/cmake/linux/bin/cmake -E cmake_autogen /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug/CMakeFiles/RayData_autogen.dir/AutogenInfo.cmake Debug

qrc_resources.cpp: ../resources/earth1.png
qrc_resources.cpp: ../resources/cube.obj
qrc_resources.cpp: ../resources/teapot2.obj
qrc_resources.cpp: ../resources/europa.png
qrc_resources.cpp: ../resources/map.png
qrc_resources.cpp: ../resources/mapZoom.png
qrc_resources.cpp: ../resources/spheres.txt
qrc_resources.cpp: ../resources/data0.txt
qrc_resources.cpp: ../resources/dataBCN.txt
qrc_resources.cpp: ../resources/dataBCNZoom.txt
qrc_resources.cpp: ../resources/dadesEuropa.txt
qrc_resources.cpp: ../resources/spheres2.txt
qrc_resources.cpp: ../resources/fitted.txt
qrc_resources.cpp: ../resources.qrc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating qrc_resources.cpp"
	/usr/lib/x86_64-linux-gnu/qt5/bin/rcc --name resources --output /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug/qrc_resources.cpp /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/resources.qrc

RayData_autogen: CMakeFiles/RayData_autogen
RayData_autogen: qrc_resources.cpp
RayData_autogen: CMakeFiles/RayData_autogen.dir/build.make

.PHONY : RayData_autogen

# Rule to build all files generated by this target.
CMakeFiles/RayData_autogen.dir/build: RayData_autogen

.PHONY : CMakeFiles/RayData_autogen.dir/build

CMakeFiles/RayData_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RayData_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RayData_autogen.dir/clean

CMakeFiles/RayData_autogen.dir/depend:
	cd /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02 /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02 /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug /home/desgarrador/Escritorio/3o/2n_semestre/Grafics/Proyectos/P1/dataray-givd02/cmake-build-debug/CMakeFiles/RayData_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RayData_autogen.dir/depend

