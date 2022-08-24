cmake_minimum_required(VERSION 3.16)

project(pixel-games LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)

#Subdirectories

if(WIN32)
else()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

#Special instructions in Debug mode
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
endif()

#generated libraries

list(APPEND libs
)

#System exclusive instructions
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    set(CMAKE_CXX_FLAGS -no-pie)
endif()

#Main program
add_executable(Program src/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "PixelGames Starter")

if (WIN32)
    target_link_libraries(Program PRIVATE "${libs}")
	
	set_target_properties("${libs}" PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else()
    target_link_libraries(Program PRIVATE "${libs}")
endif()
