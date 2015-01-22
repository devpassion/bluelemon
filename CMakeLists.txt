cmake_minimum_required(VERSION 2.6)
SET(CMAKE_TOOLCHAIN_FILE "cmake/pi.cmake" )
project(bluelemon)

include_directories( includes )

add_definitions( "-std=c++11" )

add_executable(bluelemon main.cpp)

install(TARGETS bluelemon RUNTIME DESTINATION bin)

add_subdirectory(src)
add_subdirectory(includes)
add_subdirectory(tpl)


set( RASP_USER pi )
set( RASP_HOST 192.168.0.102)

add_upload()
add_run()