# - Try to find SDL2_mixer.
# Once done this will define:
#  SDL2_MIXER_FOUND - The system found the SDL2_mixer library.
#  SDL2_MIXER_INCLUDE_DIRS - The SDL2_mixer include directory.
#  SDL2_MIXER_LIBRARIES - The libraries needed to use SDL2_mixer.

set(SDL2_SEARCH_PATHS 
	/usr/local
	/usr
	/opt)

find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_SEARCH_PATHS})

find_library(SDL2_MIXER_LIBRARY
    NAMES SDL2_mixer
	HINTS $ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib lib/x86
    PATHS ${SDL2_SEARCH_PATHS})

set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_mixer DEFAULT_MSG SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR)

mark_as_advanced(SDL2_MIXER_INCLUDE_DIR SDL2_MIXER_LIBRARY)
