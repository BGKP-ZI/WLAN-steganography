set(EXEC WLAN_Client)

if ("${OS_TYPE}" EQUAL "UNKNOWN")
  message(FATAL_ERROR "Unknown type of OS")
else()
  if ("${OS_TYPE}" EQUAL "WINDOWS")
    add_compile_definitions(WINDOWS_SYSTEM)
    add_compile_options(
      "/O2"
    )
  endif()

  if ("${OS_TYPE}" EQUAL "LINUX")
    add_compile_definitions(LINUX_SYSTEM)
    add_compile_options(
      "-Wall"
      "-Wextra"
      "-O2"
    )
  endif()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(UI_HEADERS
  ${PROJECT_ROOT_DIR}/Graphics/sources/mainwindow/mainwindow.ui
  ${PROJECT_ROOT_DIR}/Graphics/sources/chats_layout/chats_layout.ui
  ${PROJECT_ROOT_DIR}/Graphics/sources/network_layout/network_layout.ui
  ${PROJECT_ROOT_DIR}/Graphics/sources/settings_layout/settings_layout.ui
)

set(HEADERS
  ${PROJECT_ROOT_DIR}/Graphics/sources/mainwindow/mainwindow.hh
  ${PROJECT_ROOT_DIR}/Graphics/sources/chats_layout/chats_layout.hh
  ${PROJECT_ROOT_DIR}/Graphics/sources/network_layout/network_layout.hh
  ${PROJECT_ROOT_DIR}/Graphics/sources/settings_layout/settings_layout.hh

  ${PROJECT_ROOT_DIR}/Crypto/include/DataLoader.hh
  ${PROJECT_ROOT_DIR}/Network/include/WLAN.hh
  ${PROJECT_ROOT_DIR}/Network/include/Address.hh
  ${PROJECT_ROOT_DIR}/HICCUPS/include/HICCUPS.hh
  ${PROJECT_ROOT_DIR}/HICCUPS/include/RawData.hh
)

set_property(SOURCE ${HEADERS} PROPERTY SKIP_AUTOGEN ON)

set (SOURCES
  ${PROJECT_ROOT_DIR}/Graphics/sources/main.cc
  ${PROJECT_ROOT_DIR}/Graphics/sources/mainwindow/mainwindow.cc
  ${PROJECT_ROOT_DIR}/Graphics/sources/chats_layout/chats_layout.cc
  ${PROJECT_ROOT_DIR}/Graphics/sources/network_layout/network_layout.cc
  ${PROJECT_ROOT_DIR}/Graphics/sources/settings_layout/settings_layout.cc

  ${PROJECT_ROOT_DIR}/Network/sources/nix_WLAN.cc
  ${PROJECT_ROOT_DIR}/Network/sources/IfConfig.cc
  ${PROJECT_ROOT_DIR}/Network/sources/WLAN_header.cc

  ${PROJECT_ROOT_DIR}/HICCUPS/sources/HICCUPS.cc
  ${PROJECT_ROOT_DIR}/HICCUPS/sources/RawData.cc

  ${PROJECT_ROOT_DIR}/Crypto/sources/Chippers.cc
  ${PROJECT_ROOT_DIR}/Crypto/sources/KeyGenerator.cc
  ${PROJECT_ROOT_DIR}/Crypto/sources/DataLoader.cc
)

set (RESOURCES
  ${PROJECT_ROOT_DIR}/Graphics/resources/resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(${EXEC} 
    MANUAL_FINALIZATION
    ${RESOURCES}
    ${SOURCES} 
    ${HEADERS} 
    ${UI_HEADERS}
  )
else()
  add_executable(${EXEC}
    ${RESOURCES}  
    ${SOURCES} 
    ${HEADERS} 
    ${UI_HEADERS}
  )
endif()

include_directories(
    ${PROJECT_ROOT_DIR}/Graphics/sources/
    ${PROJECT_ROOT_DIR}/Network/include/
    ${PROJECT_ROOT_DIR}/Crypto/include/
    ${PROJECT_ROOT_DIR}/HICCUPS/include/
)

target_link_libraries(${EXEC} PRIVATE 
  Qt${QT_VERSION_MAJOR}::Core 
  Qt${QT_VERSION_MAJOR}::Widgets 
  Qt${QT_VERSION_MAJOR}::Gui
)
