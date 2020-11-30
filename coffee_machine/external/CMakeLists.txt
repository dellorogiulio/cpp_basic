cmake_minimum_required(VERSION 3.10)
project(external)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0054 NEW)

set(CMAKE_CXX_STANDARD 17)

set(external_src_dir
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
)

set(external_header_dir
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include_directories(include) 

####### JSON LIBRARY #######
set(catch_header_dir
  ${external_header_dir}/nlohmann
)

set(catch_source_dir
  ${external_src_dir}/nlohmann
)

add_library(json SHARED
  ${catch_header_dir}/json.hpp
  ${catch_source_dir}/json.cpp
)

add_library(nlohmann::json ALIAS json)

target_include_directories(json PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include
)