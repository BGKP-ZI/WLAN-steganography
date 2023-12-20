set(OUTFILE DataLoader)

set(SOURCES 
    DataLoader_test.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} crypto_slib)

