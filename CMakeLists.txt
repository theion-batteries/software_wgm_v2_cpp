# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(wgm VERSION "1.0")

# Tell CMake to run python from the directory where this CMakeLists file exists.
#execute_process(COMMAND python server_delta.py
#    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/tests)
#execute_process(COMMAND python server_keyence.py
#    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/tests)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
## library name
set(WGM wgm)
set(WGM_STATIC ${wgm}-static)

# --- Build Options ---

if(WIN32)
	option(WGM_BUILD_STATIC "Build static library" ON)
	option(WGM_BUILD_SHARED "Build shared library (DLL)" OFF)
else()
	option(WGM_BUILD_STATIC "Build static library" OFF)
	option(WGM_BUILD_SHARED "Build shared library" ON)
endif()

option(WGM_BUILD_EXAMPLES "Build example applications" OFF)
option(WGM_BUILD_TESTS "Build unit tests" OFF)
option(WGM_BUILD_DOCUMENTATION "Create Doxygen reference documentation" OFF)

# --- System libraries ---

include(GNUInstallDirs)

if(WIN32)
	set(LIBS_SYSTEM ws2_32)
elseif(UNIX)
	set(LIBS_SYSTEM c stdc++)
endif()

# add libraries

# include libs
include_directories(${PROJECT_SOURCE_DIR}/includes/)

# source *.cpp
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
# add .exe
add_executable(wgm ${all_SRCS})

## include preinstalled lib with vcpkg
INCLUDE_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/lib/
) 


