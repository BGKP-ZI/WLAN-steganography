set(OUTFILE SimpleXOR)

set(SOURCES 
	SimpleXOR_test.cc
	${PROJECT_ROOT_DIR}/Crypto/sources/Chippers.cc
    ${PROJECT_ROOT_DIR}/Crypto/sources/KeyGenerator.cc
)

set(HEADERS 
	${PROJECT_ROOT_DIR}/Crypto/include/Chippers.hh
)

include_directories(${PROJECT_ROOT_DIR}/Crypto/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})
