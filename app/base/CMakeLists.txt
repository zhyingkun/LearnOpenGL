# cmake_minimum_required(VERSION 3.0)
# project(base)
aux_source_directory(./src MAIN_SRC)
aux_source_directory(../common/src COMMON_SRC)
file(GLOB HEADER "./src/*.h")
file(GLOB COMMON_HEADER "../common/include/*.h")
source_group(src FILES ${MAIN_SRC} ${HEADER})
source_group(common FILES ${COMMON_SRC} ${COMMON_HEADER})
file(GLOB SHADER_FILES "./shaders/*")
file(GLOB TEXTURE_FILES "./textures/*")
source_group(shaders FILES ${SHADER_FILES})
source_group(textures FILES ${TEXTURE_FILES})
add_executable(base
	${MAIN_SRC}
	${COMMON_SRC}
	${HEADER}
	${COMMON_HEADER}
	${SHADER_FILES}
	${TEXTURE_FILES})
set(BASE_RESOURCE ${SHADER_FILES} ${TEXTURE_FILES})
set_target_properties(base PROPERTIES
	MACOSX_BUNDLE TRUE
	RESOURCE "${BASE_RESOURCE}")
target_link_libraries(base glfw glad stb_image)

find_package(OpenGL REQUIRED)
target_include_directories(base PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(base ${OPENGL_gl_LIBRARY})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(base ${CMAKE_DL_LIBS})
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
