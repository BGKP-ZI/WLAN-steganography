set(OUTFILE ip_address.exe)

set(SOURCES 
    ip_test.cc 
    ${PROJECT_ROOT_DIR}/sources/Network/IPv4Address.cc
)

set(HEADERS 
    ${PROJECT_ROOT_DIR}/include/Network/IPv4Address.hh
)

include_directories(${PROJECT_ROOT_DIR}/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})