# - Try to find SDL2
# Once done this will define
#  SDL2_FOUND - System has SDL2
#  SDL2_INCLUDE_DIRS - The SDL2 include directory
#  SDL2_LIBRARIES - The libraries needed to use SDL2
#  SDL2_DEFINITIONS - Compiler switches required for using SDL2

SET(SDL2_SEARCH_PATHS
	/usr/local
	/usr
	/opt
)

FIND_PATH(SDL2_INCLUDE_DIR SDL.h
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_SEARCH_PATHS}
)

FIND_LIBRARY(SDL2_LIBRARY
    NAMES SDL2
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib lib/x86
    PATHS ${SDL2_SEARCH_PATHS}
)

SET(SDL2_LIBRARIES ${SDL2_LIBRARY})
SET(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set SDL2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_LIBRARY SDL2_INCLUDE_DIR)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)
