cmake_minimum_required(VERSION 3.16)
project(QTtt LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Widgets Test Gui Svg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib/Directions)
add_subdirectory(lib/GameCore)
add_subdirectory(app)
if(NOT ANDROID)
    enable_testing(true)
    add_subdirectory(tests/TestDirections)
    add_subdirectory(tests/TestGameCore)
endif()
