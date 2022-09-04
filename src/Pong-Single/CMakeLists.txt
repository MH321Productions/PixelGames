# CMake file for Pong-Single

list(APPEND srcFiles
    Main.cpp Objects.cpp
)

add_executable(Pong-Single ${srcFiles})
target_link_libraries(Pong-Single sfml-graphics Util)

if(WIN32)
set_target_properties(Pong-Single PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_libraries(Pong-Single sfml-main)
install(TARGETS Pong-Single RUNTIME DESTINATION PixelGames/bin)
endif(WIN32)
