unix {
    LIBS += \
        -L$$PWD/bin -lGameCore \
        -L$$PWD/bin -lDirections
}
win32 {
    LIBS += \
        $$PWD/bin/GameCore.lib \
        $$PWD/bin/Directions.lib
}

INCLUDEPATH += \
    $$PWD/lib/Directions \
    $$PWD/lib/GameCore

DEPENDPATH += \
    $$PWD/lib/Directions \
    $$PWD/lib/GameCore
