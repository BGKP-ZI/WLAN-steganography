set(OUTFILE wlan_sender.exe)

set(SOURCES 
    wlan_sender.cc
    ${PROJECT_ROOT_DIR}/sources/Network/WLAN.cc
)

set(HEADERS 
    ${PROJECT_ROOT_DIR}/include/Network/WLAN.hh
)

include_directories(${PROJECT_ROOT_DIR}/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})