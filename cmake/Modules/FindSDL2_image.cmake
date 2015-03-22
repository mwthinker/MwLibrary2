# - Try to find SDL2_image.
# Once done this will define:
#  SDL2_IMAGE_FOUND - The system found the SDL2_image library.
#  SDL2_IMAGE_INCLUDE_DIRS - The SDL2_image include directory.
#  SDL2_IMAGE_LIBRARIES - The libraries needed to use SDL2_image.

set(SDL2_SEARCH_PATHS 
	/usr/local
	/usr
	/opt) 

find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_SEARCH_PATHS})

find_library(SDL2_IMAGE_LIBRARY
    NAMES SDL2_image
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib lib/x86
    PATHS ${SDL2_SEARCH_PATHS})

set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})
set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_image DEFAULT_MSG SDL2_IMAGE_LIBRARY SDL2_IMAGE_INCLUDE_DIR)

mark_as_advanced(SDL2_IMAGE_INCLUDE_DIR SDL2_IMAGE_LIBRARY)
