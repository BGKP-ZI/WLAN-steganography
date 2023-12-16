set(OUTFILE BBS_test)

set(SOURCES 
	BBS_test.cc
	${PROJECT_ROOT_DIR}/Crypto/sources/KeyGenerator.cc
)

set(HEADERS 
	${PROJECT_ROOT_DIR}/Crypto/include/KeyGenerator.hh
)

include_directories(${PROJECT_ROOT_DIR}/Crypto/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})
