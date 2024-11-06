QT  += quick qml

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060204    # disables all the APIs deprecated before Qt 6.0.0

VPATH += ./src

SOURCES += \
    game.cpp \
    gamePaintedItem.cpp \
    main.cpp

HEADERS += \
    game.h \
    gamePaintedItem.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

resources.files += \
    src/main.qml \
    images/Over.jpg \
    images/Z.jpg \
    images/A.jpg \
    images/AWin.jpg \
    images/Y.jpg \
    images/YWin.jpg
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
