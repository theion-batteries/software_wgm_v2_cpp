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

add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)  

###################### Build Library ############################

# lib src
file(GLOB lib_SRCS
"${PROJECT_SOURCE_DIR}/src/wgm_communication.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_monitoring.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_test.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_user.cpp"
"${PROJECT_SOURCE_DIR}/src/processes/*.cpp"
"${PROJECT_SOURCE_DIR}/src/systems/*.cpp"

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
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/processes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/systems/

# wafer holder motion system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes
# cnt system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cnt_system_submodule_cpp/includes
)

############################# build executable  ###################################

# source *.cpp
file(GLOB exe_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/processes/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/systems/*.cpp"
    )
# add .exe
add_executable(wgm_app_exe ${exe_SRCS})
# link againt static lib
target_link_libraries(wgm_app_exe
# wafer holder system static
PUBLIC whs_static
# cnt lib
PUBLIC cnt_system_static
)

target_include_directories(wgm_app_exe 
# parent deps headers
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/processes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/systems/
# wafer holder motion system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes
# cnt system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cnt_system_submodule_cpp/includes
)