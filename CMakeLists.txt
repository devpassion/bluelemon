cmake_minimum_required(VERSION 2.6)
SET(CMAKE_TOOLCHAIN_FILE "cmake/pi.cmake" )
project(bluelemon)

include_directories( includes /usr/local/include )

add_definitions( "-std=c++11" )

add_executable(bluelemon main.cpp src/io_exception.cpp)

install(TARGETS bluelemon RUNTIME DESTINATION bin)

add_subdirectory(src)
add_subdirectory(includes)
add_subdirectory(tpl)


set( RASP_USER pi )
set( RASP_HOST bluelemon)

add_upload()
add_run()