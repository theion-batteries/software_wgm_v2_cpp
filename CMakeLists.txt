############################
###### Cmake template ######
############################

# author: sami dhiab
# email: sami@theion.de
cmake_minimum_required(VERSION 3.5.0)

# project name
project(wgm_core VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# add dependencies cmake
add_subdirectory(dependencies/soft_wafer_holder_system_controller)
add_subdirectory(dependencies/soft_cnt_system_submodule_cpp)

###################### Build Library ############################

# lib src
file(GLOB lib_SRCS
"${PROJECT_SOURCE_DIR}/src/wgm_communication.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_monitoring.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_test.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_user.cpp"
"${PROJECT_SOURCE_DIR}/src/wafer_cooling_system.cpp"
"${PROJECT_SOURCE_DIR}/src/wafer_holder_motion_system.cpp"
"${PROJECT_SOURCE_DIR}/src/heating_system.cpp"
"${PROJECT_SOURCE_DIR}/src/cnt_alignment_system.cpp"
"${PROJECT_SOURCE_DIR}/src/feedback_management.cpp"
"${PROJECT_SOURCE_DIR}/src/process_manager.cpp"
)
# add .exe
add_library(wgm_static STATIC ${lib_SRCS})

# link againt static lib
target_link_libraries(wgm_static
# wafer holder system static
PUBLIC whs_static
# cnt lib
PUBLIC cnt_system_static
)

target_include_directories(wgm_static 
# parent deps headers
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes
# wafer holder motion system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes
# cnt system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cnt_system_submodule_cpp/includes
)

############################# build executable  ###################################

## source *.cpp
#file(GLOB exe_SRCS
#    "${PROJECT_SOURCE_DIR}/src/*.cpp"
#    )
## add .exe
#add_executable(wgm_app_exe ${exe_SRCS})
#
### child static and dynamic linking
## link againt static lib
#target_link_libraries(wgm_app_exe 
## wafer holder system static
#PUBLIC ${PROJECT_SOURCE_DIR}/build/dependencies/soft_wafer_holder_system_controller/Debug/whs_static.lib
## wrapper keyence static 
#PUBLIC ${PROJECT_SOURCE_DIR}/build/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_sdk/Debug/keyence_lib_static.lib
## keyence sdk static
#PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_sdk/Samples/VC_Src/Libx64/LKIF2.lib
## cnt lib
#PUBLIC ${PROJECT_SOURCE_DIR}/build/dependencies/soft_cnt_system_submodule_cpp/Debug/cnt_system_static.lib
## common dependencies::
## sockpp static
#PUBLIC ${PROJECT_SOURCE_DIR}/build/dependencies/soft_wafer_holder_system_controller/dependencies/sockpp/Debug/sockpp-static.lib
## yaml-cpp static
#PUBLIC ${PROJECT_SOURCE_DIR}/build/dependencies/soft_wafer_holder_system_controller/dependencies/yaml-cpp/Debug/libyaml-cppmdd.lib
#)
#
#
#
#

