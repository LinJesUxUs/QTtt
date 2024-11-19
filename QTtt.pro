TEMPLATE = subdirs

# CONFIG += ordered

SUBDIRS += \
    app \
    lib \
    tests

tests.depends = lib
app.depends = lib

message($$PWD)
message($$OUT_PWD)
