set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt_add_executable(QTtt MANUAL_FINALIZATION
    src/main.cpp
    src/gamestatusimageprovider.h
    src/gamestatusimageprovider.cpp
)

target_include_directories(QTtt PRIVATE src)

qt_add_qml_module(QTtt
    URI linjesuxus.settingsProxy
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES
        src/ViewsComposer.qml
        src/WelcomeView.qml
        src/IconButton.qml
        src/GameView.qml
        src/TextAndSpinBox.qml
    SOURCES
        src/settingsproxy.h src/settingsproxy.cpp
        src/gamepainteditem.h src/gamepainteditem.cpp
)

qt_add_resources(QTtt "images"
    PREFIX "/"
    FILES
        images/Alice.jpg
        images/AliceWin.jpg
        images/Bob.jpg
        images/BobWin.jpg
        images/Chuck.jpg
        images/BackGround.jpg
        images/QTttExit.svg
        images/QTttMenu.svg
        images/QTttRestart.svg
        images/QTttPlay.svg
)

target_link_libraries(QTtt PRIVATE Qt6::Widgets Qt6::Quick Qt6::Qml GameCore Directions)
if(ANDROID)
    set_property(TARGET QTtt PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    qt_finalize_executable(QTtt)
endif()

####PROJECT_METADATA_FILES#########################################

set(PROJECT_METADATA_FILES
    ../.github/workflows/reusable-build.yml
    ../.github/workflows/ci-dev.yml
    ../.github/workflows/cd-master.yml
    ../README.md
    ../.gitignore
)
set_source_files_properties(${PROJECT_METADATA_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
target_sources(QTtt PRIVATE ${PROJECT_METADATA_FILES})
source_group("GitHub" FILES ${PROJECT_METADATA_FILES})

####ANDROID_BUNDLE_FILES#########################################

set(ANDROID_BUNDLE_FILES
    android/AndroidManifest.xml
    android/build.gradle
    android/gradle.properties
    android/res/values/libs.xml
)
set_source_files_properties(${ANDROID_BUNDLE_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
target_sources(QTtt PRIVATE ${ANDROID_BUNDLE_FILES})
source_group("Android" FILES ${ANDROID_BUNDLE_FILES})
