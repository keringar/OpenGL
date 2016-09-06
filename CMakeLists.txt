cmake_minimum_required(VERSION 3.1)
project(OpenGL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
list(APPEND CMAKE_CXX_FLAGS "-static -Wall -Weffc++ -Werror -std=c++14")
list(APPEND CMAKE_EXE_LINKER_FLAGS "")

if(WIN32)
	#Hide console window
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Project sources
list(APPEND SOURCE_FILES src/main.cpp src/Util.cpp src/Window.cpp src/Game.cpp src/Input.cpp src/Tilemap.cpp src/EventDispatcher.cpp)
list(APPEND SOURCE_FILES src/Renderer/Camera.cpp src/Renderer/Shader.cpp  src/Renderer/TextRenderer.cpp src/Renderer/Texture2D.cpp src/Renderer/StaticRenderer.cpp)
add_executable(OpenGL ${SOURCE_FILES})

#Project includes
target_include_directories(OpenGL PUBLIC include)

#Build GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)
target_include_directories(OpenGL SYSTEM PUBLIC deps/glfw/include)
target_link_libraries(OpenGL glfw)

#GLAD
target_include_directories(OpenGL SYSTEM PUBLIC deps/glad/include)
target_sources(OpenGL PUBLIC deps/glad/src/glad.c)

#GLM
target_include_directories(OpenGL SYSTEM PUBLIC deps/glm)

#STB HEADERS
target_include_directories(OpenGL SYSTEM PUBLIC deps/stb)
target_sources(OpenGL PUBLIC deps/stb/stb_vorbis.c)

#Build OpenAL-soft
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
set(ALSOFT_CONFIG OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL OFF CACHE BOOL "" FORCE)
set(ALSOFT_STATIC_LIBGCC ON CACHE BOOL "" FORCE)
set(ALSOFT_EMBED_HRTF_DATA ON CACHE BOOL "" FORCE)
add_subdirectory(deps/openal-soft)
target_include_directories(OpenGL SYSTEM PUBLIC deps/openal-soft/include)
IF(WIN32)
    target_link_libraries(OpenGL OpenAL32)
ELSE()
    target_link_libraries(OpenGL openal)
ENDIF()
