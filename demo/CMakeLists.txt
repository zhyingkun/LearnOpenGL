cmake_minimum_required(VERSION 3.0)
project(app
	VERSION 1.0.0
	# DESCRIPTION "OpenGL Application Demos"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

include_directories(../libs/glfw/include)
include_directories(../libs/glm/include)
include_directories(../libs/glad/include)
include_directories(../libs/stb/include)

message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")

add_subdirectory(glfw-win)
add_subdirectory(martix-calculator)
