cmake_minimum_required(VERSION 3.10.0)
project(WLAN_steganography VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)
message(STATUS "Found Qt: Qt${QT_VERSION_MAJOR}")

if(UNIX AND NOT APPLE)
  set(OS_TYPE "LINUX")
else()
  if (MSVC OR MSYS OR MINGW)
    set(OS_TYPE "WINDOWS")
  else()
    set(OS_TYPE "UNKNOWN")
  endif()
endif ()

add_subdirectory(Network)
add_subdirectory(Crypto)
add_subdirectory(HICCUPS)
add_subdirectory(Graphics)
