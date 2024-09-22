# Install script for directory: E:/code/C/cantian/pkg/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "E:/code/C/cantian/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/common/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/driver/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/kernel/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/server/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/ctsql/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/protocol/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/rc/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/mec/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/tms/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/utils/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/cms/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/cluster/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/tse/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/fdsa/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/ctrst/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/dbstool/cmake_install.cmake")
  include("E:/code/C/cantian/out/build/x64-Debug/pkg/src/ctbox/cmake_install.cmake")

endif()

