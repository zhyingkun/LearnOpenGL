cmake_minimum_required(VERSION 3.0)
project(LearnOpenGL)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(./libs/glfw/include)
include_directories(./libs/glm/include)
include_directories(./libs/glad/include)
include_directories(./libs/stb_image/include)
include_directories(./app/common/include)

add_subdirectory(./libs)
add_subdirectory(./app)
