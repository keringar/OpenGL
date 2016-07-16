cmake_minimum_required(VERSION 3.5)
project(OpenGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(OpenAL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

set(SOURCE_FILES src/main.cpp src/glad.c src/Util.cpp src/Window.cpp src/Game.cpp src/Renderer/Renderer.cpp src/Input.cpp src/Renderer/Shader.cpp src/Renderer/Camera.cpp src/Renderer/Texture2D.cpp src/Tile.cpp)
add_executable(OpenGL ${SOURCE_FILES})

target_include_directories(OpenGL PUBLIC include)
target_link_libraries(OpenGL glfw openal)

add_custom_command(TARGET OpenGL POST_BUILD COMMAND rm -rf $(CMAKE_BINARY_DIR)/shaders)
add_custom_command(TARGET OpenGL POST_BUILD COMMAND cp -rf $(CMAKE_SOURCE_DIR)/shaders $(CMAKE_BINARY_DIR)/)