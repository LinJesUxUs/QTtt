QT += quick qml

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    $$PWD/../lib/GameCore \
    $$PWD/../lib/Directions

VPATH += $$PWD/src

SOURCES += \
    gamepainteditem.cpp \
    main.cpp

HEADERS += \
    gamepainteditem.h

TARGET = QTtt

unix {
    LIBS += \
        -L$$PWD/../lib/GameCore/bin -lGameCore \
        -L$$PWD/../lib/Directions/bin -lDirections \
        -L$$PWD/../lib/bin/build -lGameCore \
        -L$$PWD/../lib/bin/build -lDirections \
        -L$$PWD/../bin/build/lib -lDirections \
        -L$$PWD/../bin/build/lib -lGameCore
}
win32 {
    LIBS += \
        $$PWD/../lib/GameCore/bin/GameCore.lib \
        $$PWD/../lib/Directions/bin/Directions.lib \
        $$PWD/../lib/bin/build/GameCore.lib \
        $$PWD/../lib/bin/build/Directions.lib \
        $$PWD/./../bin/build/lib/Directions.lib \
        $$PWD/./../bin/build/lib/GameCore.lib
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

resources.files += \
    src/main.qml \
    images/over.jpg \
    images/z.jpg \
    images/a.jpg \
    images/awin.jpg \
    images/y.jpg \
    images/ywin.jpg
resources.prefix = /

RESOURCES = resources

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
