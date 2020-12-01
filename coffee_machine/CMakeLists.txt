
cmake_minimum_required(VERSION 3.10)

project(coffee_machine)

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories(include) 

add_subdirectory(external)

# HARDWARE VENDOR LIBRARY
file(GLOB hardware_vendor_sources "src/lib/hardware_vendor/*.cpp")

add_library(hardware_vendor_lib SHARED
	${hardware_vendor_sources}
)


target_include_directories(hardware_vendor_lib PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include
)

## OUR CODE
file(GLOB implementation_sources "src/lib/implementation/*.cpp")

add_library(implementation SHARED
	${implementation_sources}
)


target_include_directories(implementation PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
"$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include
)


target_link_libraries(implementation hardware_vendor_lib nlohmann::json)


add_executable(coffee_machine
	src/main.cpp
)

target_link_libraries(coffee_machine nlohmann::json implementation)
