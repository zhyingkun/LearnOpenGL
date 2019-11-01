cmake_minimum_required(VERSION 3.0)
project(glfw-win
	VERSION 0.1.0.0
	# DESCRIPTION "glfw window"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

if(APPLE)
	set(CMAKE_CXX_FLAGS         "-std=c++11 -Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG   "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_CXX_FLAGS         "-std=c++11 -Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG   "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(WIN32)
	set(CMAKE_CXX_FLAGS         "-Wall")
	# set(CMAKE_CXX_FLAGS_DEBUG   "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

aux_source_directory(./src MAIN_SRC)
source_group(src FILES ${MAIN_SRC})

add_executable(${PROJECT_NAME} ${MAIN_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER "app"
	MACOSX_BUNDLE TRUE
)
target_link_libraries(${PROJECT_NAME} glfw glad)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
