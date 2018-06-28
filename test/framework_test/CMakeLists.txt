cmake_minimum_required(VERSION 3.7)

project(SparrowFrameworkTest)

include_directories(${CMAKE_HOME_DIRECTORY}/deps/glfw/include)
include_directories(${CMAKE_HOME_DIRECTORY}/viscera/tools)
include_directories(include)

aux_source_directory(src FRAMEWORK_TEST_SOURCE)

add_executable(${PROJECT_NAME} ${FRAMEWORK_TEST_SOURCE})

if(OS_Darwin)
    FILE(COPY ${CMAKE_HOME_DIRECTORY}/test/framework_test/assets DESTINATION ${CMAKE_HOME_DIRECTORY}/build/bin)
elseif(OS_WINDOWS)
    FILE(COPY ${CMAKE_HOME_DIRECTORY}/test/framework_test/assets DESTINATION ${CMAKE_HOME_DIRECTORY}/build/bin/${CMAKE_BUILD_TYPE})
endif()

target_link_libraries(${PROJECT_NAME} glfw Sparrow)