cmake_minimum_required(VERSION 2.8.12)
project(OpenGL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -Wall -Werror -std=c++14")

if(WIN32)
	#Hide console window
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

set(SOURCE_FILES src/glad/glad.c src/main.cpp src/Util.cpp src/Window.cpp src/Game.cpp src/Renderer/TileRenderer.cpp src/Input.cpp src/Renderer/Shader.cpp src/Renderer/Camera.cpp src/Renderer/Texture2D.cpp src/Tilemap.cpp src/Renderer/TextRenderer.cpp)
add_executable(OpenGL ${SOURCE_FILES})

#GLFW Source
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)
target_include_directories(OpenGL SYSTEM PUBLIC deps/glfw/include)

#Header only libraries
target_include_directories(OpenGL SYSTEM PUBLIC deps/include PUBLIC deps/glm)

#Actually written by me
target_include_directories(OpenGL PUBLIC include)

target_link_libraries(OpenGL glfw)