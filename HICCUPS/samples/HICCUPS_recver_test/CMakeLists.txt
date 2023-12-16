set(OUTFILE HICCUPS_recver)

set(SOURCES 
  HICCUPS_recver_test.cc
	${PROJECT_ROOT_DIR}/Crypto/sources/Chippers.cc
  ${PROJECT_ROOT_DIR}/Crypto/sources/KeyGenerator.cc
  ${PROJECT_ROOT_DIR}/Crypto/sources/DataLoader.cc

  ${PROJECT_ROOT_DIR}/Network/sources/WLAN_header.cc
  ${PROJECT_ROOT_DIR}/Network/sources/IfConfig.cc

  ${PROJECT_ROOT_DIR}/HICCUPS/sources/HICCUPS.cc
  ${PROJECT_ROOT_DIR}/HICCUPS/sources/RawData.cc
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
	${PROJECT_ROOT_DIR}/HICCUPS/include/HICCUPS.hh
  ${PROJECT_ROOT_DIR}/Crypto/include/DataLoader.hh
  ${PROJECT_ROOT_DIR}/Network/include/WLAN.hh
  ${PROJECT_ROOT_DIR}/Network/include/Address.hh
  ${PROJECT_ROOT_DIR}/HICCUPS/include/RawData.hh
)

include_directories(
  ${PROJECT_ROOT_DIR}/HICCUPS/include/
  ${PROJECT_ROOT_DIR}/Network/include
  ${PROJECT_ROOT_DIR}/Crypto/include
)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})