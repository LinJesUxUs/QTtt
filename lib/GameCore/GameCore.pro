QT += core
QT -= gui

TEMPLATE = lib

CONFIG += c++11 staticlib

include(../../definitions.pri)
include(../../libIncludes.pri)

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204

# INCLUDEPATH += $$PWD/../Directions

SOURCES += \
    gamecore.cpp

HEADERS += \
    gamecore.h

# Default rules for deployment.
# unix {
#     target.path = $$[QT_INSTALL_PLUGINS]/generic
#     LIBS += \
#         -L$$PWD/../Directions/bin -lDirections \
#         -L$$PWD/../bin/build -lDirections \
#         -L$$PWD/../../bin/build/lib -lDirections
# }
# win32 {
#     LIBS += \
#         $$PWD/../Directions/bin/Directions.lib \
#         $$PWD/../bin/build/Directions.lib \
#         $$PWD/../../bin/build/lib/Directions.lib
# }
# !isEmpty(target.path): INSTALLS += target
