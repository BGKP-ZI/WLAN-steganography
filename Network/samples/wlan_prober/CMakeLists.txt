set(OUTFILE wlan_prober)

set(SOURCES 
    wlan_prober.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} network_slib)
