CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(MwLibrary2)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
if (WIN32)
	# Exception handler model.
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc -D_SCL_SECURE_NO_WARNINGS")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /EHsc")
	
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
	
	SET( CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /nodefaultlib:libcmt.lib /nodefaultlib:msvcrt")
	SET( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /nodefaultlib:libcmt.lib /nodefaultlib:msvcrt.lib")
else (WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++11")
endif (WIN32)
# Source files.
SET(SOURCES
src/mw/exception.h
src/mw/initsdl.cpp
src/mw/initsdl.h
src/mw/initttf.cpp
src/mw/initttf.h
src/mw/sound.cpp
src/mw/sound.h
src/mw/soundbuffer.cpp
src/mw/soundbuffer.h
src/mw/sprite.cpp
src/mw/sprite.h
src/mw/soundbuffer.cpp
src/mw/soundbuffer.h
src/mw/text.cpp
src/mw/text.h
src/mw/texture.cpp
src/mw/texture.h
src/mw/window.cpp
src/mw/window.h
src/mw/font.cpp
src/mw/font.h
src/mw/music.h)
# End of source files.
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)
FIND_PACKAGE(SDL2_mixer REQUIRED)
FIND_PACKAGE(SDL2_ttf REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${OPENGL_LIBRARIES})
ADD_LIBRARY(MwLibrary2 ${SOURCES})
