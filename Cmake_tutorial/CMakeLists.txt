cmake_minimum_required(VERSION 3.10)

#project(server)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(server server.cpp)
add_executable(client client.cpp)
target_link_libraries(server wsock32 ws2_32)
target_link_libraries(client wsock32 ws2_32)

#
### in terminal:
# mkdir build
# cmake -B ./build
#
### build and run exe in debug
# cmake --build ./build
#
### build and run in release
# cmake --build ./build --config Release