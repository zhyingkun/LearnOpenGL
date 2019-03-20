cmake_minimum_required(VERSION 3.0)
project(stb_image
	VERSION 1.0.0
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

include_directories(./include)

aux_source_directory(./src STB_IMAGE_SRC)
file(GLOB STB_IMAGE_HEADER "./include/*.h")

source_group(src FILES ${STB_IMAGE_SRC})
source_group(include FILES ${STB_IMAGE_HEADER})

if(WIN32)
	add_library(${PROJECT_NAME} STATIC ${STB_IMAGE_SRC} ${STB_IMAGE_HEADER})
else(WIN32)
	add_library(${PROJECT_NAME} SHARED ${STB_IMAGE_SRC} ${STB_IMAGE_HEADER})
endif(WIN32)
