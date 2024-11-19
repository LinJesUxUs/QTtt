QT += testlib core
QT -= gui

CONFIG += qt object console warn_on depend_includepath testcase

TEMPLATE += app

INCLUDEPATH += \
    $$PWD/../../lib/GameCore \
    $$PWD/../../lib/Directions

unix {
    LIBS += \
        -L$$PWD/../../lib/GameCore/bin -lGameCore \
        -L$$PWD/../../lib/Directions/bin -lDirections \
        -L$$PWD/../../lib/bin/build -lGameCore \
        -L$$PWD/../../lib/bin/build -lDirections \
        -L$$PWD/../../bin/build/lib -lDirections \
        -L$$PWD/../../bin/build/lib -lGameCore
}
win32 {
    LIBS += \
        $$PWD/../../lib/GameCore/bin/GameCore.lib \
        $$PWD/../../lib/Directions/bin/Directions.lib \
        $$PWD/../../lib/bin/build/GameCore.lib \
        $$PWD/../../lib/bin/build/Directions.lib \
        $$PWD/../../bin/build/lib/Directions.lib \
        $$PWD/../../bin/build/lib/GameCore.lib
}

SOURCES += \
    TestGameCore.cpp

TARGET = bin/$$TARGET
