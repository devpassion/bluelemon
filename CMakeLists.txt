cmake_minimum_required(VERSION 2.6)
set( RASP_USER pi )
set( RASP_HOST bluelemon)
SET( RASPTOOLS_PATH /home/tim288/prog/lib/rasp )
SET(CMAKE_TOOLCHAIN_FILE "cmake/pi.cmake" )
project(bluelemon)

include_directories( includes /usr/local/include )

add_definitions( "-std=c++11" )
add_definitions( "-Os -s" )

# add_definitions( "-findirect-inlining -finline-functions -finline-functions-called-once -finline-small-functions" )

add_subdirectory(src)
add_subdirectory(includes)
add_subdirectory(tpl)

add_executable(bluelemon main.cpp src/io_exception.cpp  )

install(TARGETS bluelemon RUNTIME DESTINATION bin)






add_upload()
add_run()