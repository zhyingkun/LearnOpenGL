cmake_minimum_required(VERSION 3.0)
project(app)

include_directories(../libs/glfw/include)
include_directories(../libs/glm/include)
include_directories(../libs/glad/include)
include_directories(../libs/stb/include)
include_directories(./common/include)

add_subdirectory(./glfw-win)
add_subdirectory(./base)
add_subdirectory(./template)
add_subdirectory(./martix-calculator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET glfw-win PROPERTY FOLDER "app")
set_property(TARGET base PROPERTY FOLDER "app")
set_property(TARGET template PROPERTY FOLDER "app")
set_property(TARGET martix-calculator PROPERTY FOLDER "app")
