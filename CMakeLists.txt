cmake_minimum_required(VERSION 3.10)
project(SocketProject)

set(CMAKE_CXX_STANDARD 11)

add_library(lib SHARED ${CMAKE_SOURCE_DIR}/lib/library.cpp)

add_executable(program1 program1/program1.cpp)
target_link_libraries(program1 lib)

add_executable(program2 program2/program2.cpp)
target_link_libraries(program2 lib)
