QT += testlib core
QT -= gui

CONFIG += qt object console warn_on depend_includepath testcase

TEMPLATE += app

include(../../definitions.pri)
include(../../libIncludes.pri)

SOURCES += \
    TestDirections.cpp
