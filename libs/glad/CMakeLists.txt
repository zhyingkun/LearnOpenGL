cmake_minimum_required(VERSION 3.0)
project(glad
	VERSION 1.0.0
	LANGUAGES C CXX
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

if(APPLE)
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(CMAKE_C_FLAGS         "-std=c11 -Wall -Wextra")
	set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
elseif(WIN32)
	set(CMAKE_C_FLAGS         "-Wall")
	# set(CMAKE_C_FLAGS_DEBUG   "-g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

include_directories(./include)

aux_source_directory(./src GLAD_SRC)
set(GLAD_HEADER
	./include/glad/glad.h
	./include/KHR/khrplatform.h
)

source_group(src FILES ${GLAD_SRC})
source_group(include FILES ${GLAD_HEADER})

if(WIN32)
	add_library(${PROJECT_NAME} STATIC ${GLAD_SRC} ${GLAD_HEADER})
else(WIN32)
	add_library(${PROJECT_NAME} SHARED ${GLAD_SRC} ${GLAD_HEADER})
endif(WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER "libs"
)
