#include "initsdl.h"

#include <SDL.h>

namespace mw {

	InitSdl::InitSdl() {
		if (nbrOfInstances < 1) {
			if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) ) {
				//printf( "Unable to init SDL: %s\n", SDL_GetError() );
			}
		}
		++nbrOfInstances;
	}

	InitSdl::~InitSdl() {
		//--nbrOfInstances;
		if (nbrOfInstances < 1) {
			//SDL_Quit();
		}
	}

	int InitSdl::nbrOfInstances = 0;

} // Namespace mw.
