# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.22.0)

# project name
project(wgm_v2)

# creates the variable EXEC and sets it to hello
set(EXEC main)

# set the C++14 standard
set(CMAKE_CXX_STANDARD 17)

# I../includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../includes/)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp)