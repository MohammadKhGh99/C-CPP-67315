# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /cygdrive/c/Users/m7mdg/AppData/Local/JetBrains/CLion2020.2/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/m7mdg/AppData/Local/JetBrains/CLion2020.2/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/d/C&C++LionProjects/C++/examCPP"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/examCPP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/examCPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/examCPP.dir/flags.make

CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.o: CMakeFiles/examCPP.dir/flags.make
CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.o: ../HighestStudentGrade.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.o -c "/cygdrive/d/C&C++LionProjects/C++/examCPP/HighestStudentGrade.cpp"

CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/d/C&C++LionProjects/C++/examCPP/HighestStudentGrade.cpp" > CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.i

CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/d/C&C++LionProjects/C++/examCPP/HighestStudentGrade.cpp" -o CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.s

CMakeFiles/examCPP.dir/PresubmissionTests.cpp.o: CMakeFiles/examCPP.dir/flags.make
CMakeFiles/examCPP.dir/PresubmissionTests.cpp.o: ../PresubmissionTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/examCPP.dir/PresubmissionTests.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/examCPP.dir/PresubmissionTests.cpp.o -c "/cygdrive/d/C&C++LionProjects/C++/examCPP/PresubmissionTests.cpp"

CMakeFiles/examCPP.dir/PresubmissionTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/examCPP.dir/PresubmissionTests.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/d/C&C++LionProjects/C++/examCPP/PresubmissionTests.cpp" > CMakeFiles/examCPP.dir/PresubmissionTests.cpp.i

CMakeFiles/examCPP.dir/PresubmissionTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/examCPP.dir/PresubmissionTests.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/d/C&C++LionProjects/C++/examCPP/PresubmissionTests.cpp" -o CMakeFiles/examCPP.dir/PresubmissionTests.cpp.s

# Object files for target examCPP
examCPP_OBJECTS = \
"CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.o" \
"CMakeFiles/examCPP.dir/PresubmissionTests.cpp.o"

# External object files for target examCPP
examCPP_EXTERNAL_OBJECTS =

examCPP.exe: CMakeFiles/examCPP.dir/HighestStudentGrade.cpp.o
examCPP.exe: CMakeFiles/examCPP.dir/PresubmissionTests.cpp.o
examCPP.exe: CMakeFiles/examCPP.dir/build.make
examCPP.exe: CMakeFiles/examCPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable examCPP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/examCPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/examCPP.dir/build: examCPP.exe

.PHONY : CMakeFiles/examCPP.dir/build

CMakeFiles/examCPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/examCPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/examCPP.dir/clean

CMakeFiles/examCPP.dir/depend:
	cd "/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/d/C&C++LionProjects/C++/examCPP" "/cygdrive/d/C&C++LionProjects/C++/examCPP" "/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug" "/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug" "/cygdrive/d/C&C++LionProjects/C++/examCPP/cmake-build-debug/CMakeFiles/examCPP.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/examCPP.dir/depend
