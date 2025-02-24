cmake_minimum_required(VERSION 3.10)

project(FirstTestProject)

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_library(mylib SHARED lib/mylib.cpp)

add_executable(program1 program1/main.cpp)
target_link_libraries(program1 mylib)

add_executable(program2 program2/main.cpp)
target_link_libraries(program2 mylib)

add_executable(server server/server.cpp)
target_link_libraries(server mylib)
