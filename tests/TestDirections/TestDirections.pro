QT += testlib core
QT -= gui

CONFIG += qt object console warn_on depend_includepath testcase

TEMPLATE += app

INCLUDEPATH += ../../lib/Directions

unix:LIBS += -L$$PWD/../../lib/Directions/bin -lDirections
win32:LIBS += $$PWD/../../lib/Directions/bin/Directions.lib

SOURCES += \
    TestDirections.cpp
