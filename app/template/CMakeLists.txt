aux_source_directory(./src MAIN_SRC)
add_executable(template ${MAIN_SRC})

target_link_libraries(template glfw glad)

find_package(OpenGL REQUIRED)
target_include_directories(template PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(template ${OPENGL_gl_LIBRARY})
