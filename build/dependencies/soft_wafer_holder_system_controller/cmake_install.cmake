# Install script for directory: C:/Users/SamiDhiab/Theion_Repos/software_wgm_v2_cpp/dependencies/soft_wafer_holder_system_controller

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/wgm_core")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/SamiDhiab/Theion_Repos/software_wgm_v2_cpp/build/dependencies/soft_wafer_holder_system_controller/dependencies/sockpp/cmake_install.cmake")
  include("C:/Users/SamiDhiab/Theion_Repos/software_wgm_v2_cpp/build/dependencies/soft_wafer_holder_system_controller/dependencies/lib_keyence_sdk/cmake_install.cmake")
  include("C:/Users/SamiDhiab/Theion_Repos/software_wgm_v2_cpp/build/dependencies/soft_wafer_holder_system_controller/dependencies/yaml-cpp/cmake_install.cmake")

endif()

