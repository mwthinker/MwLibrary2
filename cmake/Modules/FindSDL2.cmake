# - Try to find SDL2.
# Once done this will define:
#  SDL2_FOUND - The system found the SDL2 library.
#  SDL2_INCLUDE_DIRS - The SDL2 include directory
#  SDL2_LIBRARIES - The libraries needed to use SDL2.

set(SDL2_SEARCH_PATHS
	/usr/local
	/usr
	/opt)

find_path(SDL2_INCLUDE_DIR SDL.h
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_SEARCH_PATHS})

find_library(SDL2_LIBRARY
    NAMES SDL2
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib lib/x86
    PATHS ${SDL2_SEARCH_PATHS})

if (WIN32)
	find_library(SDL2MAIN_LIBRARY
		NAMES SDL2main
		HINTS $ENV{SDL2DIR}
		PATH_SUFFIXES lib64 lib lib/x86
		PATHS ${SDL2_SEARCH_PATHS})
		
	set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})
else ()
	set(SDL2_LIBRARIES ${SDL2_LIBRARY})
endif ()

set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_LIBRARY SDL2MAIN_LIBRARY SDL2_INCLUDE_DIR)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY SDL2MAIN_LIBRARY)
