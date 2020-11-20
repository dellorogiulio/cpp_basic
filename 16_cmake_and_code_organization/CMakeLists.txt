#	CMAKE
# CMake is a scripiting language which simplify the make file generation
# A CMakeLists.txt file is used to provide information to cmake about executable, libraries, etc but is not limited to this!


# here a minimal version of a CMakeLists.txt file

cmake_minimum_required(VERSION 3.10) # cmake minimum version

project(cpp_course_demo) # a project name

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build") #say to the compiler where to put the executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") #say to the compiler where to put the executables

include_directories(include) #include directory for the compiler

# How a Cpp folder should be organized? Well, it's argument of debate and there is no standard 
# Here we present our structure which keeps header, source, etc well organized 
# + root
# 	+ build: builded files goes here
#	+ include: header files
#		- my_class.h
#	+ src: source files go here
#		+ lib: files which will not be executable go here
# 			- my_class.cpp 
#		- main.cpp : all cpp files containg a main function go here
#	- CMakeLists.txt: main CMake file


# here we add an exacutable linking che main.cpp and the lib file my_class.cpp
add_executable(main
	src/main.cpp
	src/lib/my_class.cpp
)
