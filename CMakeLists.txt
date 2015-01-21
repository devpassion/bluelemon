cmake_minimum_required(VERSION 2.6)
project(metarasp)

add_executable(metarasp main.cpp)

install(TARGETS metarasp RUNTIME DESTINATION bin)
