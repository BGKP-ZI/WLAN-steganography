set(OUTFILE wlan_sender)

set(SOURCES 
    wlan_sender.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} network_slib)

