set(LIB_NAME network_slib)

if ("${OS_TYPE}" EQUAL "UNKNOWN")
  message(FATAL_ERROR "Unknown type of OS")
else()
  message(STATUS "Detected OS type: ${OS_TYPE}")
  if ("${OS_TYPE}" STREQUAL "WINDOWS")
    add_compile_definitions(WINDOWS_SYSTEM)
    add_compile_options(
      "/O2"
    )
    set(LIB_SOURCES ${PROJECT_ROOT_DIR}/Network/sources/win_WLAN.cc)
  endif()

  if ("${OS_TYPE}" STREQUAL "LINUX")
    add_compile_definitions(LINUX_SYSTEM)
    add_compile_options(
      "-Wall"
      "-Wextra"
      "-O2"
    )
    set(LIB_SOURCES ${PROJECT_ROOT_DIR}/Network/sources/nix_WLAN.cc)
  endif()
endif()

set(LIB_SOURCES 
  ${LIB_SOURCES}
  ${PROJECT_ROOT_DIR}/Network/sources/IfConfig.cc
  ${PROJECT_ROOT_DIR}/Network/sources/WLAN_header.cc
)
set(LIB_HEADERS
  ${PROJECT_ROOT_DIR}/Network/include/WLAN.hh
  ${PROJECT_ROOT_DIR}/Network/include/Address.hh
  ${PROJECT_ROOT_DIR}/Network/include/RegEx.hh
)

add_library(${LIB_NAME} SHARED
  ${LIB_SOURCES}
  ${LIB_HEADERS}
)

target_include_directories(${LIB_NAME} PUBLIC
  ${PROJECT_ROOT_DIR}/Network/include/
)

add_subdirectory(samples)
