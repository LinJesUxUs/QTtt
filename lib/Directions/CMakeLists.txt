add_library(Directions STATIC directions.cpp directions.h)
target_include_directories(Directions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Directions PRIVATE Qt6::Core)
