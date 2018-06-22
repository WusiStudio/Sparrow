cmake_minimum_required(VERSION 3.7)

project(SparrowInitTest)

message(${CMAKE_HOME_DIRECTORY})

include_directories(${CMAKE_HOME_DIRECTORY}/deps/glfw/include)
include_directories(${CMAKE_HOME_DIRECTORY}/viscera/tools)

add_executable(${PROJECT_NAME} main.cpp)

# if(OS_Darwin)
#     find_library(COCOA_LIBRARY Cocoa required)
#     find_library(OPENGL_LIBRARY OpenGL required)
#     find_library(IOKIT_LIBRARY IOKit required)
#     target_link_libraries(${PROJECT_NAME} ${IOKIT_LIBRARY}/IOKit.tbd)
# endif(OS_Darwin)

target_link_libraries(${PROJECT_NAME} glfw)