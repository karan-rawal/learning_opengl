cmake_minimum_required(VERSION 3.30)
project(learning_opengl)

set(CMAKE_CXX_STANDARD 20)

add_executable(learning_opengl main.cpp)

find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(
        learning_opengl
        PRIVATE glfw
)