add_library(GameCore STATIC gamecore.cpp gamecore.h)
target_include_directories(GameCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GameCore PUBLIC Qt6::Core Directions)
