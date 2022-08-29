# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(wgm VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# include libs
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes/)

# source *.cpp
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/src/whs_controller.cpp"
)
# add .exe
add_executable(wgm_app ${all_SRCS})

## include preinstalled lib with vcpkg
INCLUDE_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/lib/
) 


