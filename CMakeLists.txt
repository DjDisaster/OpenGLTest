cmake_minimum_required(VERSION 3.16)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled2 src/main.cpp)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(untitled2
        glfw
        OpenGL::GL
        GLEW::GLEW
)