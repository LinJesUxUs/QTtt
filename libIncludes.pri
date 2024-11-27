unix|win32 {
    LIBS += \
        -L$$PWD/bin -lGameCore \
        -L$$PWD/bin -lDirections
}

android {
    for (abi, ANDROID_ABIS): ANDROID_EXTRA_LIBS += \
        $$PWD/bin/libGameCore_$${abi}.so \
        $$PWD/bin/libDirections_$${abi}.so
}

INCLUDEPATH += \
    $$PWD/lib/Directions \
    $$PWD/lib/GameCore

DEPENDPATH += \
    $$PWD/lib/Directions \
    $$PWD/lib/GameCore
