cmake_minimum_required(VERSION 2.8.12)
project(OpenGL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++14")

#GLFW Source
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

set(SOURCE_FILES src/main.cpp src/glad.c src/Util.cpp src/Window.cpp src/Game.cpp src/Renderer/TileRenderer.cpp src/Input.cpp src/Renderer/Shader.cpp src/Renderer/Camera.cpp src/Renderer/Texture2D.cpp src/Tilemap.cpp src/FastNoise.cpp)
add_executable(OpenGL ${SOURCE_FILES})

target_include_directories(OpenGL PUBLIC include)

target_link_libraries(OpenGL glfw)
