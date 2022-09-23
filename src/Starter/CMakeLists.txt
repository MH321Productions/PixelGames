#CMake file for the program starter

list(APPEND starterSrc
    StarterFrame.cpp
    StarterImpl.cpp
    AboutDialog.cpp
    LibrariesDialog.cpp
    LibraryPanel.cpp
    IPC/IPC.cpp
    IPC/IPCPosix.cpp
    IPC/IPCWindows.cpp
)

add_executable(Starter ${starterSrc})
target_link_libraries(Starter PRIVATE wx::base wx::core Util Resources)

if(WIN32)
    install(TARGETS Starter RUNTIME DESTINATION PixelGames/bin)
    set_target_properties(Starter PROPERTIES WIN32_EXECUTABLE TRUE)
endif()