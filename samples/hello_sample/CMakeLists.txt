set(OUTFILE hello_sample.exe)

set(SOURCES 
    hello.cc
)

include_directories(${PROJECT_ROOT_DIR}/include)

add_executable(${OUTFILE} ${SOURCES} ${HEADERS})