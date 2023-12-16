set(OUTFILE wlan_sender)

set(SOURCES 
    wlan_sender.cc
    ${PROJECT_ROOT_DIR}/Network/sources/WLAN_header.cc
    ${PROJECT_ROOT_DIR}/Network/sources/IfConfig.cc
)

if ("${OS_TYPE}" STREQUAL "UNKNOWN")
  message(FATAL_ERROR "Unknown type of OS")
else()
#WIN_SYSTEM
  if ("${OS_TYPE}" STREQUAL "WINDOWS")
    set(SOURCES 
      ${SOURCES}
      ${PROJECT_ROOT_DIR}/Network/sources/win_WLAN.cc
    )
  endif("${OS_TYPE}" STREQUAL "WINDOWS")
#NIX_SYSTEM
  if ("${OS_TYPE}" STREQUAL "LINUX")
    set(SOURCES 
      ${SOURCES}
      ${PROJECT_ROOT_DIR}/Network/sources/nix_WLAN.cc
    )
  endif("${OS_TYPE}" STREQUAL "LINUX")
endif()

set(HEADERS 
    ${PROJECT_ROOT_DIR}/Network/include/WLAN.hh
)

include_directories(${PROJECT_ROOT_DIR}/Network/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})
