#加载Qt模块
QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#配置
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#源文件
SOURCES += \
    main.cpp \
    widget.cpp

#头文件
HEADERS += \
    widget.h

#下面这些其实都可以不要，删掉也可以正常运行
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
