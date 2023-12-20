set(LIB_NAME crypto_slib)

set(LIB_SOURCES 
  ${PROJECT_ROOT_DIR}/Crypto/sources/Chippers.cc
  ${PROJECT_ROOT_DIR}/Crypto/sources/DataLoader.cc
  ${PROJECT_ROOT_DIR}/Crypto/sources/KeyGenerator.cc
)
set(LIB_HEADERS
    ${PROJECT_ROOT_DIR}/Crypto/include/Chippers.hh
    ${PROJECT_ROOT_DIR}/Crypto/include/DataLoader.hh
    ${PROJECT_ROOT_DIR}/Crypto/include/KeyGenerator.hh
)

add_library(${LIB_NAME} SHARED
  ${LIB_SOURCES}
  ${LIB_HEADERS}
)

target_include_directories(${LIB_NAME} PUBLIC
  ${PROJECT_ROOT_DIR}/Crypto/include/
)

add_subdirectory(samples)
