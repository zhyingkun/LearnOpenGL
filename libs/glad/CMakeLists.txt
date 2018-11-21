# cmake_minimum_required(VERSION 3.0)
# project(libs)
include_directories(./include)
aux_source_directory(./src GLAD_SRC)
set(GLAD_HEADER
	./include/glad/glad.h
	./include/KHR/khrplatform.h)
source_group(src FILES ${GLAD_SRC})
source_group(header FILES ${GLAD_HEADER})
if(WIN32)
	add_library(glad STATIC ${GLAD_SRC} ${GLAD_HEADER})
else(WIN32)
	add_library(glad SHARED ${GLAD_SRC} ${GLAD_HEADER})
endif(WIN32)