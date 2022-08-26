# CMake file for Pong-Single

list(APPEND srcFiles
    Main.cpp Objects.cpp
)

add_executable(Pong-Single ${srcFiles})
target_link_libraries(Pong-Single sfml-graphics Util)