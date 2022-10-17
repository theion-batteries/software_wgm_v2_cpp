# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(wgm VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include libs
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes/)
## child includes
include_directories(${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_distance_sensor/dependencies/sockpp/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_sdk/includes)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/yaml-cpp/include/)

# source *.cpp
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/src/whs_controller.cpp"
## child includes
    "${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_distance_sensor/dependencies/sockpp/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_sdk/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/yaml-cpp/src/*.cpp"
    )

# add .exe
add_executable(wgm_app ${all_SRCS})

## child static and dynamic linking
# link againt static lib
target_link_libraries(wgm_app ${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_sdk/LKIF2.lib
									 ${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/yaml-cpp/build/Debug/libyaml-cppmdd.lib

)

## include preinstalled lib with vcpkg
INCLUDE_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/lib/
) 


