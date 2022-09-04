# CMake file for the resource formatter

add_executable(Resource-Formatter Formatter.cpp FormatterImpl.cpp)
target_link_libraries(Resource-Formatter wx::base wx::core Util)

if(WIN32)
    set_target_properties(Resource-Formatter PROPERTIES WIN32_EXECUTABLE TRUE)
endif()