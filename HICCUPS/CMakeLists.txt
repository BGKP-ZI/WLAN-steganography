set(LIB_NAME HICCUPS_slib)

set(LIB_SOURCES 
  ${PROJECT_ROOT_DIR}/HICCUPS/sources/HICCUPS.cc
  ${PROJECT_ROOT_DIR}/HICCUPS/sources/RawData.cc
)
set(LIB_HEADERS
  ${PROJECT_ROOT_DIR}/HICCUPS/include/HICCUPS.hh
  ${PROJECT_ROOT_DIR}/HICCUPS/include/RawData.hh
)

add_library(${LIB_NAME} SHARED
  ${LIB_SOURCES}
  ${LIB_HEADERS}
)

target_include_directories(${LIB_NAME} PUBLIC
  ${PROJECT_ROOT_DIR}/HICCUPS/include/
)

target_link_libraries(${LIB_NAME}
    network_slib
    crypto_slib
)

add_subdirectory(samples)