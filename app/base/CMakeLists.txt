cmake_minimum_required(VERSION 3.0)
project(base
	VERSION 0.1.0.0
	# DESCRIPTION "OpenGL base app"
	# HOMEPAGE_URL "www.zhyingkun.com"
	LANGUAGES C CXX)

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
	set(CMAKE_CXX_FLAGS         "-std=c++11 -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG   "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

aux_source_directory(./src MAIN_SRC)
aux_source_directory(../common/src COMMON_SRC)
file(GLOB HEADER "./src/*.h")
file(GLOB COMMON_HEADER "../common/include/*.h")

source_group(src FILES ${MAIN_SRC} ${HEADER})
source_group(common FILES ${COMMON_SRC} ${COMMON_HEADER})

file(GLOB SHADER_FILES "./shaders/*")
file(GLOB TEXTURE_FILES "../resources/textures/*")
source_group(shaders FILES ${SHADER_FILES})
source_group(textures FILES ${TEXTURE_FILES})

add_executable(${PROJECT_NAME}
	${MAIN_SRC}
	${COMMON_SRC}
	${HEADER}
	${COMMON_HEADER}
	${SHADER_FILES}
	${TEXTURE_FILES})
set(BASE_RESOURCE ${SHADER_FILES} ${TEXTURE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE TRUE
	RESOURCE "${BASE_RESOURCE}")# Here must has "", if not, will failed in cmake 3.13.1
target_link_libraries(${PROJECT_NAME} glfw glad stb)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
