set(OUTFILE HICCUPS_recver)

set(SOURCES 
  HICCUPS_recver_test.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} HICCUPS_slib)
