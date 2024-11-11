QT += testlib core
QT -= gui

CONFIG += qt object console warn_on depend_includepath testcase
# CONFIG -= app_bundle

# TEMPLATE = app

TARGET = test

SOURCES += \
    test_game.cpp \
    ../src/game.cpp

HEADERS += \
    test_game.h \
    ../src/game.h
