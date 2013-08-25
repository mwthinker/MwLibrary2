#include "initsdl.h"

#include <SDL.h>

namespace mw {

	InitSdl::InitSdl() {
		if (nbrOfInstances_ < 1) {
			if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) ) {
				//printf( "Unable to init SDL: %s\n", SDL_GetError() );
			}
		}
		++nbrOfInstances_;
	}

	InitSdl::~InitSdl() {
		--nbrOfInstances_;
		if (nbrOfInstances_ < 1) {
			SDL_Quit();
		}
	}

	InitSdl::InitSdl(const InitSdl&) {
		++nbrOfInstances_;
	}

	InitSdl& InitSdl::operator=(const InitSdl&) {
		++nbrOfInstances_;
		return *this;
	}	

	int InitSdl::nbrOfInstances_ = 0;

} // Namespace mw.
