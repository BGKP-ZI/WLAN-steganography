set(OUTFILE BBS_test)

set(SOURCES 
	BBS_test.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} crypto_slib)

