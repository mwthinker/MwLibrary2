# - Try to find GLEW.
# Once done this will define:
#  GLEW_FOUND - The system found the GLEW library.
#  GLEW_INCLUDE_DIR - The GLEW include directory.
#  GLEW_LIBRARY - The library needed to use GLEW.

set(GLEW_SEARCH_PATHS
	/usr/local
	/usr
	/opt)

find_path(GLEW_INCLUDE_DIR GL/glew.h
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES include/GLEW include
    PATHS ${GLEW_SEARCH_PATHS})

find_library(GLEW_LIBRARY
	NAMES GLEW glew32 glew glew32s
	HINTS $ENV{SDL2DIR}	
	PATH_SUFFIXES PATH_SUFFIXES lib64 lib lib/Release/Win32
	PATHS ${GLEW_SEARCH_PATHS})

set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
set(GLEW_LIBRARIES ${GLEW_LIBRARY})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_LIBRARY GLEW_INCLUDE_DIR)

mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY)
