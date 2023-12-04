#请求cmake执行的最小版本
cmake_minimum_required(VERSION 3.5)

#指定项目信息（项目名称 项目版本 项目使用语言（CXX=C++））
project(Qt3 VERSION 0.1 LANGUAGES CXX)

#头文件是否包含当前目录
#自动uic/moc/rcc
set(CMAKE_AUTOUIC ON)   #有ui文件的时候，会自动生成源代码
set(CMAKE_AUTOMOC ON)   #是否自动元编译
set(CMAKE_AUTORCC ON)   #是否自动编译资源文件

#设置C++的标准为17
set(CMAKE_CXX_STANDARD 17)
#强制设置C++标准，如果不支持C++17则会发生错误
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找模块
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#项目文件（代码 资源 ui文件）
set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Qt3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Qt3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Qt3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

#给目标连接库：
target_link_libraries(Qt3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Qt3)
endif()

set_target_properties(Qt3 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Qt3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
#终止生成
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qt3)
endif()
