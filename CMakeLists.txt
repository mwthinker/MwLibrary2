cmake_minimum_required(VERSION 2.8)
project(MwLibrary2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "-std=c++1y")
	option(Debug "Set projects to debug mode.")
	if (Debug)
		set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Build type.")
		add_definitions(-D_DEBUG)
	else ()
		set(CMAKE_BUILD_TYPE "Release" CACHE INTERNAL "Build type.")
	endif ()
endif ()

option(MwLibrary2Test "Add MwLibrary2Test project." OFF)

# Source files.
set(SOURCES
	src/mw/buffer.cpp
	src/mw/buffer.h
	src/mw/color.h
	src/mw/font.cpp
	src/mw/font.h
	src/mw/initsdl.cpp
	src/mw/initsdl.h
	src/mw/initttf.cpp
	src/mw/initttf.h
	src/mw/joystick.cpp
	src/mw/joystick.h
	src/mw/matrix44.h
	src/mw/vec2.h
	src/mw/music.cpp
	src/mw/music.h
	src/mw/opengl.cpp
	src/mw/opengl.h
	src/mw/shader.cpp
	src/mw/shader.h
	src/mw/sound.cpp
	src/mw/sound.h
	src/mw/initmixer.cpp
	src/mw/initmixer.h
	src/mw/sprite.cpp
	src/mw/sprite.h
	src/mw/text.cpp
	src/mw/text.h
	src/mw/texture.cpp
	src/mw/texture.h
	src/mw/textureatlas.cpp
	src/mw/textureatlas.h
	src/mw/vertexarrayobject.cpp
	src/mw/vertexarrayobject.h
	src/mw/vertexbufferobject.cpp
	src/mw/vertexbufferobject.h
	src/mw/vertexdata.cpp
	src/mw/vertexdata.h
	src/mw/window.cpp
	src/mw/window.h
)

set(SOURCES_TEST
	srcTest/drawtext.cpp
	srcTest/drawtext.h
	srcTest/testshader.cpp
	srcTest/testshader.h
	srcTest/testshaderdata.h
	srcTest/main.cpp
	srcTest/testwindow.cpp
	srcTest/testwindow.h
)

# End of source files.

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS})

add_library(MwLibrary2 ${SOURCES})

set(ALL_MW_LIBRARIES
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES})

if (MwLibrary2Test)
	include_directories(src)
	add_executable(MwLibrary2Test ${SOURCES_TEST})

	if (MSVC)
		set_target_properties(MwLibrary2Test PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:msvcrt")
	endif ()

	target_link_libraries(MwLibrary2Test MwLibrary2 ${ALL_MW_LIBRARIES})

	file(COPY dataTest/. DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) # Copy data to build folder.
endif ()
