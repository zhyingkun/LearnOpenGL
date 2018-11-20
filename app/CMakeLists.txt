# cmake_minimum_required(VERSION 3.0)
# project(app)
add_subdirectory(./base)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET base PROPERTY FOLDER "app")
