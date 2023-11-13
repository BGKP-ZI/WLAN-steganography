set(EXEC test_graph)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(UI_HEADERS
    ${PROJECT_ROOT_DIR}/include/Graphics/mainwindow.ui
    ${PROJECT_ROOT_DIR}/include/Graphics/chats.ui
    ${PROJECT_ROOT_DIR}/include/Graphics/network.ui
    ${PROJECT_ROOT_DIR}/include/Graphics/settings.ui
)

set(HEADERS
    ${PROJECT_ROOT_DIR}/include/Graphics/mainwindow.hh
    ${PROJECT_ROOT_DIR}/include/Graphics/chats.hh
    ${PROJECT_ROOT_DIR}/include/Graphics/network.hh
    ${PROJECT_ROOT_DIR}/include/Graphics/settings.hh
)

set_property(SOURCE ${HEADERS} PROPERTY SKIP_AUTOGEN ON)

set (SOURCES
    ./main.cc
    ${PROJECT_ROOT_DIR}/sources/Graphics/chats.cc 
    ${PROJECT_ROOT_DIR}/sources/Graphics/mainwindow.cc 
    ${PROJECT_ROOT_DIR}/sources/Graphics/network.cc
    ${PROJECT_ROOT_DIR}/sources/Graphics/settings.cc 
)


qt_add_executable(${EXEC} 
    MANUAL_FINALIZATION
    ${SOURCES} 
    ${HEADERS} 
    ${UI_HEADERS}
)

include_directories(
    ${PROJECT_ROOT_DIR}/include/
)

target_link_libraries(${EXEC} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
