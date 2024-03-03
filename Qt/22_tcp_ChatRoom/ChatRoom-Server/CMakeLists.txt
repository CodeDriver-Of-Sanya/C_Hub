cmake_minimum_required(VERSION 3.8)

project(ChatRoom-Server)

find_package(Qt6 COMPONENTS Core Network REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

aux_source_directory(./ MY_SOURCES)

add_executable(${PROJECT_NAME} ${MY_SOURCES} "Server.h" "Server.cpp")

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Network)
