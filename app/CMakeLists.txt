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
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(glfw-win)
set_property(TARGET glfw-win PROPERTY FOLDER "app")
add_subdirectory(base)
set_property(TARGET base PROPERTY FOLDER "app")
add_subdirectory(martix-calculator)
set_property(TARGET martix-calculator PROPERTY FOLDER "app")
add_subdirectory(template)
set_property(TARGET template PROPERTY FOLDER "app")
add_subdirectory(lighting)
set_property(TARGET lighting PROPERTY FOLDER "app")
