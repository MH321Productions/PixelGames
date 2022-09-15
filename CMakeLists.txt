cmake_minimum_required(VERSION 3.16)

project(pixel-games LANGUAGES CXX)

include_directories(src)
include_directories(include)

#Subdirectories
add_subdirectory(lib/SFML)
include_directories(lib/SFML/include)
set(wxBUILD_VENDOR "321Productions")
add_subdirectory(lib/wxWidgets)
include_directories(lib/wxWidgets/include)
include_directories(lib/json/single_include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
message(STATUS "Install to: ${CMAKE_INSTALL_PREFIX}")

#Special instructions in Debug mode
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
endif()

#System exclusive instructions
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    add_compile_definitions(PG_WINDOWS)
    set(PGLibType STATIC) #Have to be static on Windows, bc MSVC has a problem with linking them
else()
    set(CMAKE_CXX_FLAGS -no-pie)
    set(PGLibType SHARED)
endif()
    
#generated libraries
#add_library(Util-s STATIC src/Util/Util.cpp src/Util/Base64.cpp src/Util/Windows.cpp)
add_library(Util ${PGLibType} src/Util/Util.cpp src/Util/Base64.cpp src/Util/Windows.cpp)
add_library(Resources ${PGLibType} src/Resources/IO.cpp src/Resources/Resources.cpp src/Util/Base64.cpp)

#Minigames
add_subdirectory(src/Pong-Single)
    
#Main program
add_subdirectory(src/Starter)
add_subdirectory(src/ResFormatter)
add_executable(Main src/Main.cpp)
set_target_properties(Main PROPERTIES OUTPUT_NAME "PixelGames Starter" WIN32_EXECUTABLE TRUE)

if (WIN32)
    #set_target_properties("${libs}" PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    install(TARGETS Main RUNTIME DESTINATION PixelGames)

    #Install libraries
    install(
        TARGETS sfml-system sfml-graphics sfml-window
        CONFIGURATIONS Release
        RUNTIME DESTINATION PixelGames/bin
    )
    
    get_target_property(wxbase wx::base ALIASED_TARGET)
    get_target_property(wxcore wx::core ALIASED_TARGET)
    install(
        TARGETS ${wxbase} ${wxcore}
        RUNTIME DESTINATION PixelGames/bin
    )
endif()
