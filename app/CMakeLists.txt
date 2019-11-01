cmake_minimum_required(VERSION 3.0)
project(app
	VERSION 1.0.0
	# DESCRIPTION "OpenGL Applications"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

include_directories(../libs/glfw/include)
include_directories(../libs/glm/include)
include_directories(../libs/glad/include)
include_directories(../libs/stb/include)
include_directories(./common/include)

message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")

add_subdirectory(glfw-win)
add_subdirectory(base)
add_subdirectory(martix-calculator)
add_subdirectory(template)
add_subdirectory(lighting)
