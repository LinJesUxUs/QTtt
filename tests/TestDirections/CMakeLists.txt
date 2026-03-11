qt_add_executable(TestDirections TestDirections.cpp)
add_test(NAME TestDirections COMMAND TestDirections )
target_link_libraries(TestDirections PRIVATE Qt6::Test Qt6::Core Directions)
