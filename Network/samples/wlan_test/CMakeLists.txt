set(OUTFILE wlan_test)

set(SOURCES 
    wlan_test.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} network_slib)

