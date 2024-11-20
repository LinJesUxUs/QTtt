TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    lib \
    tests \
    app

tests.depends = lib
app.depends = lib

DISTFILES += \
    definitions.pri \
    libIncludes.pri
