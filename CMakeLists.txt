cmake_minimum_required(VERSION 3.5)
project(OpenGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(glfw3 3.2 REQUIRED)

set(SOURCE_FILES src/main.cpp src/glad.c src/Util.cpp src/Window.cpp src/Game.cpp src/Renderer.cpp include/Renderer.h src/Input.cpp include/Input.h)
add_executable(OpenGL ${SOURCE_FILES})

target_include_directories(OpenGL PUBLIC include)
target_link_libraries(OpenGL glfw)