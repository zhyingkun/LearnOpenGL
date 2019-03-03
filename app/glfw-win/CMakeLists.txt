cmake_minimum_required(VERSION 3.0)
project(glfw-win
	VERSION 0.1.0.0
	DESCRIPTION "glfw window"
	HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)
aux_source_directory(./src MAIN_SRC)
source_group(src FILES ${MAIN_SRC})
add_executable(${PROJECT_NAME} ${MAIN_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE TRUE)
target_link_libraries(${PROJECT_NAME} glfw glad)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
