# - Try to find SDL2_ttf.
# Once done this will define:
#  SDL2_TTF_FOUND - The system found the SDL2_ttf library.
#  SDL2_TTF_INCLUDE_DIRS - The SDL2_ttf include directory.
#  SDL2_TTF_LIBRARIES - The libraries needed to use SDL2_ttf.

set(SDL2_SEARCH_PATHS 
	/usr/local
	/usr
	/opt)

find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_SEARCH_PATHS})

find_library(SDL2_TTF_LIBRARY
    NAMES SDL2_ttf
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib lib/x86
    PATHS ${SDL2_SEARCH_PATHS})

set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_ttf DEFAULT_MSG SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR)

mark_as_advanced(SDL2_TTF_INCLUDE_DIR SDL2_TTF_LIBRARY)
