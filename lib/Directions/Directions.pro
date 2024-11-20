QT += core
QT -= gui

TEMPLATE = lib

CONFIG += c++11 staticlib

include(../../definitions.pri)

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204

SOURCES += \
    directions.cpp

HEADERS += \
    directions.h

# Default rules for deployment.
# unix:target.path = $$[QT_INSTALL_PLUGINS]/generic
# !isEmpty(target.path): INSTALLS += target
