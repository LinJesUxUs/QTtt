qt_add_executable(TestGameCore TestGameCore.cpp)
add_test(NAME TestGameCore COMMAND TestGameCore )
target_link_libraries(TestGameCore PRIVATE Qt6::Test Qt6::Core Directions GameCore)
