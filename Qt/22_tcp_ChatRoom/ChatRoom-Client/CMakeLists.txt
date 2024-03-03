cmake_minimum_required(VERSION 3.8)

project(ChatRoom-Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

aux_source_directory(./Util UTIL_SOURCES )

aux_source_directory(./ MY_SOURCES)

add_executable(${PROJECT_NAME}
${MY_SOURCES} "MainWindow.ui"  Util/SChatBubble.h Util/SEventfilterObject.h
${UTIL_SOURCES}
"Resource.qrc")

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Network)
