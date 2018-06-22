cmake_minimum_required(VERSION 3.7)
project(Sparrow)

set(SPARROW_VERSION_MAJOR "1")
set(SPARROW_VERSION_MINOR "0")
set(SPARROW_VERSION_PATCH "0")
set(SPARROW_VERSION_EXTRA "")
set(SPARROW_VERSION ${SPARROW_VERSION_MAJOR}.${SPARROW_VERSION_MINOR})
set(SPARROW_VERSION_FULL ${SPARROW_VERSION}.${SPARROW_VERSION_PATCH}${SPARROW_VERSION_EXTRA})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug") 

#build glfw
add_subdirectory(deps/glfw)

#设置编译选项-------------------------------------------
if ((CMAKE_SYSTEM_NAME MATCHES "Linux") OR (${CYGWIN}))
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -m64 -std=c++11 -O0 -Wall -g")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -m64 -std=c++11 -O3 -Wall")
    add_compile_options(-DCHAR_SET="UTF-8")
    add_compile_options(-DOS_LINUX)
    option(OS_LINUX "" ON )
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")  
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS}")
    add_compile_options(/source-charset:utf-8)
    add_compile_options(-DCHAR_SET="GBK")
    add_compile_options(-DOS_WINDOWS)
    option(OS_WINDOWS "" ON)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")

    find_library(OPENGL_LIBRARY OpenGL required)
    find_library(IOKIT_LIBRARY IOKit required)

    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
    add_compile_options(-std=c++11)
    add_compile_options(-Wall)
    add_compile_options(-m64)
    add_compile_options(-DCHAR_SET="UTF-8")
    add_compile_options(-DOS_Darwin)
    option(OS_Darwin "" ON)

elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
endif()

add_compile_options(-DROOT_NAMESPACE=ws)

aux_source_directory(src SOURCE)

include_directories(include)
include_directories(viscera)
include_directories(${CMAKE_HOME_DIRECTORY}/deps/glfw/include)
include_directories(deps/glm)

add_library(${PROJECT_NAME} ${SOURCE})

if(OS_Darwin)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY}/OpenGL.tbd ${IOKIT_LIBRARY}/IOKit.tbd)
endif(OS_Darwin)

add_subdirectory(test/init_test)
add_subdirectory(test/framework_test)