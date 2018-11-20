# cmake_minimum_required(VERSION 3.0)
# project(libs)

add_subdirectory(./glfw)
add_subdirectory(./glad)
add_subdirectory(./stb_image)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET glfw PROPERTY FOLDER "libs")
set_property(TARGET glad PROPERTY FOLDER "libs")
set_property(TARGET stb_image PROPERTY FOLDER "libs")
