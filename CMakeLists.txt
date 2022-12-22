cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

project(cosmic VERSION 1.0)

file(
	GLOB cosmic_src
	src/*.cpp
	deps/glad/glad.c
	deps/imgui/*.cpp
	deps/imgui/backends/imgui_impl_glfw.cpp
	deps/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(
	${PROJECT_NAME}
	${cosmic_src}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE	
	glfw
	GL
	X11
	pthread
	Xi
	dl
)

include_directories(
	src/include
	deps
	deps/glm
	deps/stb
	deps/glad
	deps/imgui
	deps/imgui/backends
	deps/glfw/include
)

target_link_directories(
	${PROJECT_NAME}	
	PRIVATE
	deps/glfw/src/
)

add_subdirectory(deps/glfw)
add_subdirectory(examples)

