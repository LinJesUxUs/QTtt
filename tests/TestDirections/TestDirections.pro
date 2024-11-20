QT += testlib core
QT -= gui

CONFIG += qt object console warn_on depend_includepath testcase

TEMPLATE += app

include(../../definitions.pri)
include(../../libIncludes.pri)

# INCLUDEPATH += $$PWD/../../lib/Directions

# unix {
#     LIBS += \
#         -L$$PWD/../../lib/Directions/bin -lDirections \
#         -L$$PWD/../../lib/bin/build -lDirections \
#         -L$$PWD/../../bin/build/lib -lDirections
# }
# win32 {
#     LIBS += \
#         $$PWD/../../lib/Directions/bin/Directions.lib \
#         $$PWD/../../lib/bin/build/Directions.lib \
#         $$PWD/../../bin/build/lib/Directions.lib
# }

SOURCES += \
    TestDirections.cpp

# TARGET = bin/$$TARGET