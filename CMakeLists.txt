cmake_minimum_required(VERSION 3.1...3.12)
project(MwLibrary2
	DESCRIPTION
		"A C++ wrapper of SDL2 and OpenGl"
	LANGUAGES
		CXX
)
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files.
set(SOURCES
	src/mw/batch.h
	src/mw/buffer.cpp
	src/mw/buffer.h
	src/mw/color.h
	src/mw/font.cpp
	src/mw/font.h
	src/mw/gamecontroller.cpp
	src/mw/gamecontroller.h
	src/mw/initmixer.cpp
	src/mw/initmixer.h
	src/mw/initsdl.cpp
	src/mw/initsdl.h
	src/mw/initttf.cpp
	src/mw/initttf.h
	src/mw/matrix44.h
	src/mw/music.cpp
	src/mw/music.h
	src/mw/opengl.cpp
	src/mw/opengl.h
	src/mw/shader.cpp
	src/mw/shader.h
	src/mw/sound.cpp
	src/mw/sound.h
	src/mw/sprite.cpp
	src/mw/sprite.h
	src/mw/text.cpp
	src/mw/text.h
	src/mw/textureatlas.cpp
	src/mw/textureatlas.h
	src/mw/texture.cpp
	src/mw/texture.h
	src/mw/vec2.h
	src/mw/vertexarrayobject.cpp
	src/mw/vertexarrayobject.h
	src/mw/vertexbufferobject.cpp
	src/mw/vertexbufferobject.h
	src/mw/vertexdata.cpp
	src/mw/vertexdata.h
	src/mw/window.cpp
	src/mw/window.h
)

add_library(MwLibrary2 ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(MwLibrary2
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
		${SDL2_INCLUDE_DIR}
		${SDL2_IMAGE_INCLUDE_DIR}
		${SDL2_TTF_INCLUDE_DIR}
		${SDL2_MIXER_INCLUDE_DIR}
		${GLEW_INCLUDE_DIRS}
)

target_link_libraries(MwLibrary2
	PUBLIC
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${SDL2_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_IMAGE_LIBRARIES}
)
	
option(MwLibrary2Test "Add MwLibrary2Test project." OFF)

if (MwLibrary2Test)
	set(SOURCES_TEST
		srcTest/batchtriangles.h
		srcTest/drawtext.cpp
		srcTest/drawtext.h
		srcTest/main.cpp
		srcTest/testshader.cpp
		srcTest/testshaderdata.h
		srcTest/testshader.h
		srcTest/testshader2.h
		srcTest/testshader2.cpp
		srcTest/testwindow2.h
		srcTest/testwindow.cpp
		srcTest/testwindow.h
	)
	
	add_executable(MwLibrary2Test ${SOURCES_TEST})
	
	target_include_directories(MwLibrary2Test
		PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/srcTest
	)

	target_link_libraries(MwLibrary2Test MwLibrary2)	
	
	file(COPY dataTest/. DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) # Copy data to build folder.
endif ()
