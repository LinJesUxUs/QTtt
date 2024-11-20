
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
# win32:CONFIG(release, debug|release): LIBS += -L$$PWD/bin -lspdr0
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/bin -lspdr0
# else:unix: LIBS += -L$$PWD/bin -lspdr

INCLUDEPATH += \
    $$PWD/lib/Directions \
    $$PWD/lib/GameCore

DEPENDPATH += \
    $$PWD/lib/Directions \
    $$PWD/lib/GameCore
