cmake_minimum_required(VERSION 3.7)

project(SparrowFrameworkTest)

message(${CMAKE_HOME_DIRECTORY})

include_directories(${CMAKE_HOME_DIRECTORY}/deps/glfw/include)
include_directories(${CMAKE_HOME_DIRECTORY}/viscera/tools)
include_directories(include)

set(SOURCE "")

aux_source_directory(src SOURCE)

add_executable(${PROJECT_NAME} ${SOURCE})

# if(OS_Darwin)
#     find_library(COCOA_LIBRARY Cocoa required)
#     find_library(OPENGL_LIBRARY OpenGL required)
#     target_link_libraries(${PROJECT_NAME} ${COCOA_LIBRARY})
# endif(OS_Darwin)

target_link_libraries(${PROJECT_NAME} glfw Sparrow)