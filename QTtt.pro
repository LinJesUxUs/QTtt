TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    lib \
    tests \
    app

tests.depends = lib
app.depends = lib

android:SUBDIRS -= tests

DISTFILES += \
    definitions.pri \
    libIncludes.pri
