cmake_minimum_required(VERSION 3.10.0)
project(WLAN_steganography VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

# Now ignore non linux system
add_compile_options(
  "-Wall"
  "-Wextra"
  "-O3"
)

find_program(IS_CLANG_FORMAT "clang-format")
if(IS_CLANG_FORMAT)
  file(GLOB_RECURSE ALL_SOURCE_FILES
      ${CMAKE_SOURCE_DIR}/sources/*.*[ch]
      ${CMAKE_SOURCE_DIR}/include/*.*[ch]
      ${CMAKE_SOURCE_DIR}/samples/*.*[ch]
  )
  if(ALL_SOURCE_FILES)
  else()
    message(STATUS "Can not find any source/header files for format target")
  endif()

  add_custom_target(
      format
      COMMAND clang-format
      -style=LLVM
      -i
      ${ALL_SOURCE_FILES}
    )
endif()

# TODO: add run target

add_subdirectory(sources)
add_subdirectory(samples)
