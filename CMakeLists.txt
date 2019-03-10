cmake_minimum_required(VERSION 3.0)
project(LearnOpenGL
	VERSION 1.0.0
	LANGUAGES C CXX)

message(STATUS "CMakeLists.txt for ${PROJECT_NAME}")
message(STATUS "Current OS is ${CMAKE_SYSTEM}")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(./libs)
add_subdirectory(./app)
