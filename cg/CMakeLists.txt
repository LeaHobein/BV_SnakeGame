# Inspired by https://www.glfw.org/docs/3.3/build_guide.html#build_link_cmake_package
# With CMake and GLFW source
# and https://github.com/meemknight/cmakeSetup as an example for a CMake setup
# Edited by Merijam Gotzes
# 13.03.2024

cmake_minimum_required(VERSION 3.27)

project(CGSnakeGame)

# Disable the build of GLFW tests, examples and documentation aso.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.4)			# window opener
add_subdirectory(external/glad)				# opengl loader
add_subdirectory(external/stb_image)	    # loading images
add_subdirectory(external/assimp)			# asset importer
add_subdirectory(external/glm)				# math

# MY_SOURCE_FILES is a list of all the source files for my implementation
# located at directory src/
file(GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}" include/GameRenderer.h include/GameMainWindow.h
        include/Grid.h
		src/Grid.cpp
		src/Box.cpp
		src/Cone.cpp
		src/Roof.cpp
		src/Sphere.cpp)

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCE_FILES} )

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE  glm glfw
	glad stb_image assimp)
