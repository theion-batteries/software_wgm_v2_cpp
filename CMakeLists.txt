############################
###### Cmake template ######
############################

# author: sami dhiab
# email: sami@theion.de
cmake_minimum_required(VERSION 3.1.0)

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
add_subdirectory(dependencies/soft_cooling_system_submodule_cpp)
add_subdirectory(dependencies/soft_heating_system_submodule)
#add_subdirectory(tests)

# add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)  

###################### Build Library ############################

# lib src
file(GLOB lib_SRCS
"${PROJECT_SOURCE_DIR}/src/wgm_communication.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_monitoring.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_test.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_user.cpp"
"${PROJECT_SOURCE_DIR}/src/wgm_experiment.cpp"
"${PROJECT_SOURCE_DIR}/src/processes/*.cpp"
"${PROJECT_SOURCE_DIR}/src/systems/*.cpp"

)
# add .exe
add_library(wgmCoreLib STATIC ${lib_SRCS})

# link againt static lib
target_link_libraries(wgmCoreLib
# wafer holder system static
PUBLIC whsLib
# cnt lib
PUBLIC cntLib
# cooling ph lib
PUBLIC coolingLib
# heating lib
PUBLIC heatingSystemLib
# link DB
PUBLIC databaseLib
)

target_include_directories(wgmCoreLib 
# parent deps headers
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/processes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/systems/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../database/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../database/sqlite3-cmake/src

# wafer holder motion system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes
# cnt system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cnt_system_submodule_cpp/includes
# cooling ph system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cooling_system_submodule_cpp/includes
# heating system 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_heating_system_submodule/includes
)
############################# build executable  ###################################
# source *.cpp
file(GLOB exe_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/processes/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/systems/*.cpp"
    )
# add .exe
add_executable(wgmCoreBin ${exe_SRCS})
# link againt static lib
target_link_libraries(wgmCoreBin
# wafer holder system static
PUBLIC whsLib
# cnt lib
PUBLIC cntLib
# cooling ph lib
PUBLIC coolingLib
# heating lib
PUBLIC heatingSystemLib
# link DB
PUBLIC databaseLib
)

target_include_directories(wgmCoreBin 
# parent deps headers
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/processes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/systems/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../database/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../database/sqlite3-cmake/src

# wafer holder motion system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_wafer_holder_system_controller/includes
# cnt system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cnt_system_submodule_cpp/includes
# cooling ph system header tree
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_cooling_system_submodule_cpp/includes
# heating system 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/soft_heating_system_submodule/includes


)

copy_dlls_keyence_target_destination(wgmCoreBin)
copy_dlls_meteor_target_destination(wgmCoreBin)
copy_dlls_yaml_target_destination(wgmCoreBin)

############################# install target lib ########################################
install(TARGETS wgmCoreLib #wgmCoreBin 
CONFIGURATIONS Debug
RUNTIME DESTINATION bin/Debug
LIBRARY DESTINATION lib)
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h" 
 "${CMAKE_CURRENT_SOURCE_DIR}/includes/processes/*.h"
 "${CMAKE_CURRENT_SOURCE_DIR}/includes/systems/*.h"
)
INSTALL(FILES ${files} DESTINATION include/wgmCoreLib/)

