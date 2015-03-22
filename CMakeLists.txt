cmake_minimum_required(VERSION 2.8)
project(MwLibrary2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
if (MSVC)
	# Exception handler model.
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHsc")
	
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -DWIN32)
else ()
	set(CMAKE_CXX_FLAGS "-std=c++11")
	set(CMAKE_BUILD_TYPE "Debug")
endif ()

option(MwLibrary2Test "MwLibrary2Test project is added" OFF)

# Source files.
set(SOURCES
	src/mw/color.h
	src/mw/exception.h
	src/mw/font.cpp
	src/mw/font.h
	src/mw/initsdl.cpp
	src/mw/initsdl.h
	src/mw/initttf.cpp
	src/mw/initttf.h
	src/mw/joystick.cpp
	src/mw/joystick.h
	src/mw/matrix.cpp
	src/mw/matrix.h	
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
	src/mw/vertexbufferobject.cpp
	src/mw/vertexbufferobject.h
	src/mw/window.cpp
	src/mw/window.h)

set(SOURCES_TEST
	srcTest/testshader.cpp
	srcTest/testshader.h
	srcTest/main.cpp
	srcTest/testwindow.cpp
	srcTest/testwindow.h)
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
	endif (MSVC)
	
	target_link_libraries(MwLibrary2Test MwLibrary2 ${ALL_MW_LIBRARIES})
	
	file(COPY dataTest/. DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) # Copy data to build folder.
endif (MwLibrary2Test)
