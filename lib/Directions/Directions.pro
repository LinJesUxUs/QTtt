QT += core
QT -= gui

TEMPLATE = lib

include(../../definitions.pri)

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204

SOURCES += \
    directions.cpp

HEADERS += \
    directions.h
