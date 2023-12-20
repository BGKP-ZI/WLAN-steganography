set(OUTFILE SimpleXOR)

set(SOURCES 
	SimpleXOR_test.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} crypto_slib)

