set(OUTFILE wlan_recver)

set(SOURCES 
    wlan_recver.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} network_slib)