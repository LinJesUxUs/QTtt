QT += core
QT -= gui

TEMPLATE = lib

CONFIG += c++11 staticlib

include(../../definitions.pri)
include(../../libIncludes.pri)

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204

SOURCES += \
    gamecore.cpp

HEADERS += \
    gamecore.h
