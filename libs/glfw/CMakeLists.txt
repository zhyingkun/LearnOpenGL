cmake_minimum_required(VERSION 3.0)
project(glfw)
if(APPLE)
	set(_GLFW_COCOA 1)
	set(GLFW_CONFIG_DIR "./config/mac")
	set(GLFW_CONFIG_H "./config/mac/glfw_config.h")
endif(APPLE)
if(WIN32)
	set(_GLFW_WIN32 1)
	set(GLFW_CONFIG_DIR "./config/windows")
	set(GLFW_CONFIG_H "./config/windows/glfw_config.h")
endif(WIN32)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(_GLFW_X11 1)
	set(GLFW_CONFIG_DIR "./config/linux")
	set(GLFW_CONFIG_H "./config/linux/glfw_config.h")
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

set(common_HEADERS
	${GLFW_CONFIG_H}
	"./src/internal.h"
	"./src/mappings.h"
	"./include/GLFW/glfw3.h"
	"./include/GLFW/glfw3native.h")
set(common_SOURCES
	"./src/context.c"
	"./src/init.c"
	"./src/input.c"
	"./src/monitor.c"
	"./src/vulkan.c"
	"./src/window.c")

if(_GLFW_COCOA)
	set(glfw_HEADERS ${common_HEADERS} ./src/cocoa_platform.h ./src/cocoa_joystick.h
	./src/posix_thread.h ./src/nsgl_context.h ./src/egl_context.h ./src/osmesa_context.h)
	set(glfw_SOURCES ${common_SOURCES} ./src/cocoa_init.m ./src/cocoa_joystick.m
	./src/cocoa_monitor.m ./src/cocoa_window.m ./src/cocoa_time.c ./src/posix_thread.c
	./src/nsgl_context.m ./src/egl_context.c ./src/osmesa_context.c)
	# For some reason, CMake doesn't know about .m
	set_source_files_properties(${glfw_SOURCES} PROPERTIES LANGUAGE C)
elseif(_GLFW_WIN32)
	set(glfw_HEADERS ${common_HEADERS} ./src/win32_platform.h ./src/win32_joystick.h
	./src/wgl_context.h ./src/egl_context.h ./src/osmesa_context.h)
	set(glfw_SOURCES ${common_SOURCES} ./src/win32_init.c ./src/win32_joystick.c
	./src/win32_monitor.c ./src/win32_time.c ./src/win32_thread.c ./src/win32_window.c
	./src/wgl_context.c ./src/egl_context.c ./src/osmesa_context.c)
elseif(_GLFW_X11)
	set(glfw_HEADERS ${common_HEADERS} ./src/x11_platform.h ./src/xkb_unicode.h ./src/posix_time.h
	./src/posix_thread.h ./src/glx_context.h ./src/egl_context.h ./src/osmesa_context.h)
	set(glfw_SOURCES ${common_SOURCES} ./src/x11_init.c ./src/x11_monitor.c ./src/x11_window.c
	./src/xkb_unicode.c ./src/posix_time.c ./src/posix_thread.c ./src/glx_context.c
	./src/egl_context.c ./src/osmesa_context.c)
	set(glfw_HEADERS ${glfw_HEADERS} ./src/linux_joystick.h)
	set(glfw_SOURCES ${glfw_SOURCES} ./src/linux_joystick.c)
endif()

#--------------------------------------------------------------------
# Use Cocoa for window creation and NSOpenGL for context creation
#--------------------------------------------------------------------
if (_GLFW_COCOA)
	list(APPEND glfw_LIBRARIES
		"-framework Cocoa"
		"-framework IOKit"
		"-framework CoreFoundation"
		"-framework CoreVideo")
endif()

#--------------------------------------------------------------------
# Use X11 for window creation
#--------------------------------------------------------------------
if (_GLFW_X11)
	find_package(X11 REQUIRED)
	# Set up library and include paths
	list(APPEND glfw_INCLUDE_DIRS "${X11_X11_INCLUDE_PATH}")
	list(APPEND glfw_LIBRARIES "${X11_X11_LIB}" "${CMAKE_THREAD_LIBS_INIT}")
	# Check for XRandR (modern resolution switching and gamma control)
	if (NOT X11_Xrandr_FOUND)
		message(FATAL_ERROR "The RandR headers were not found")
	endif()
	# Check for Xinerama (legacy multi-monitor support)
	if (NOT X11_Xinerama_FOUND)
		message(FATAL_ERROR "The Xinerama headers were not found")
	endif()
	# Check for Xkb (X keyboard extension)
	if (NOT X11_Xkb_FOUND)
		message(FATAL_ERROR "The X keyboard extension headers were not found")
	endif()
	# Check for Xcursor (cursor creation from RGBA images)
	if (NOT X11_Xcursor_FOUND)
		message(FATAL_ERROR "The Xcursor headers were not found")
	endif()
	list(APPEND glfw_INCLUDE_DIRS "${X11_Xrandr_INCLUDE_PATH}"
									"${X11_Xinerama_INCLUDE_PATH}"
									"${X11_Xkb_INCLUDE_PATH}"
									"${X11_Xcursor_INCLUDE_PATH}")
endif()

#--------------------------------------------------------------------
# Find and add Unix math and time libraries
#--------------------------------------------------------------------
if (UNIX AND NOT APPLE)
	find_library(RT_LIBRARY rt)
	mark_as_advanced(RT_LIBRARY)
	if (RT_LIBRARY)
		list(APPEND glfw_LIBRARIES "${RT_LIBRARY}")
	endif()
	find_library(MATH_LIBRARY m)
	mark_as_advanced(MATH_LIBRARY)
	if (MATH_LIBRARY)
		list(APPEND glfw_LIBRARIES "${MATH_LIBRARY}")
	endif()
	if (CMAKE_DL_LIBS)
		list(APPEND glfw_LIBRARIES "${CMAKE_DL_LIBS}")
	endif()
endif()

set(_GLFW_BUILD_DLL 1)
source_group(src FILES ${glfw_SOURCES})
source_group(header FILES ${glfw_HEADERS})
add_library(glfw SHARED ${glfw_SOURCES} ${glfw_HEADERS})
set_target_properties(glfw PROPERTIES
						OUTPUT_NAME "glfw"
						VERSION "3.3"
						SOVERSION "3"
						POSITION_INDEPENDENT_CODE ON
						FOLDER "GLFW3")
target_compile_definitions(glfw PRIVATE _GLFW_USE_CONFIG_H)
target_compile_definitions(glfw INTERFACE _GLFW_BUILD_DLL)
target_include_directories(glfw PUBLIC
							"./include")
target_include_directories(glfw PRIVATE
							"./src"
							${GLFW_CONFIG_DIR}
							${glfw_INCLUDE_DIRS})
target_link_libraries(glfw PRIVATE ${glfw_LIBRARIES})