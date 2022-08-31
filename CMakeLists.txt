cmake_minimum_required(VERSION 3.16)

project(pixel-games LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)

#Subdirectories
add_subdirectory(lib/SFML)
include_directories(lib/SFML/include)
add_subdirectory(lib/wxWidgets)
include_directories(lib/wxWidgets/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

#Special instructions in Debug mode
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
endif()

#System exclusive instructions
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    add_compile_definitions(PG_WINDOWS)
else()
    set(CMAKE_CXX_FLAGS -no-pie)
endif()
    
#generated libraries
add_library(Util STATIC src/Util/Util.cpp src/Util/Base64.cpp src/Util/Windows.cpp)
add_library(IPC STATIC src/IPC/IPC.cpp src/IPC/IPCPosix.cpp src/IPC/IPCWindows.cpp)
target_link_libraries(IPC PRIVATE wx::base)

list(APPEND libs
)

#Minigames
add_subdirectory(src/Pong-Single)
    
#Main program
add_executable(Program src/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "PixelGames Starter")

if (WIN32)
    target_link_libraries(Program PRIVATE "${libs}")

    set_target_properties("${libs}" PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else()
    target_link_libraries(Program PRIVATE "${libs}")
endif()
