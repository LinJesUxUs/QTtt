QT += core
QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204

INCLUDEPATH += ../Directions

SOURCES += \
    gamecore.cpp

HEADERS += \
    gamecore.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    LIBS += -L$$PWD/../Directions/bin -lDirections
}
win32:LIBS += $$PWD/../Directions/bin/Directions.lib
!isEmpty(target.path): INSTALLS += target
