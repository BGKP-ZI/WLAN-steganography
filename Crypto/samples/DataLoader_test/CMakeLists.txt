set(OUTFILE DataLoader)

set(SOURCES 
    DataLoader_test.cc
	${PROJECT_ROOT_DIR}/Crypto/sources/Chippers.cc
    ${PROJECT_ROOT_DIR}/Crypto/sources/KeyGenerator.cc
    ${PROJECT_ROOT_DIR}/Crypto/sources/DataLoader.cc
)

set(HEADERS 
	${PROJECT_ROOT_DIR}/Crypto/include/DataLoader.hh
)

include_directories(${PROJECT_ROOT_DIR}/Crypto/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})
