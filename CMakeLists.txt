cmake_minimum_required(VERSION 4.0)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled2 src/main.cpp)
find_package(glfw3 3.4 REQUIRED)
target_link_libraries(untitled2 glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(untitled2 OpenGL::GL)
