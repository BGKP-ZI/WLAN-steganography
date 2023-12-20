set(OUTFILE HICCUPS_sender)

set(SOURCES 
  HICCUPS_sender_test.cc
)

add_executable(${OUTFILE} ${SOURCES})

target_link_libraries(${OUTFILE} HICCUPS_slib)
