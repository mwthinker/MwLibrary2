#include "initsdl.h"

#include <SDL.h>

#include <iostream>

namespace mw {

	InitSdl::InitSdl() {
		if (nbrOfInstances < 1) {
			if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) ) {
				std::cout << "Unable to init SDL: \n" << SDL_GetError() << std::endl;
			}
		}
		++nbrOfInstances;
	}

	InitSdl::~InitSdl() {
		--nbrOfInstances;
		if (nbrOfInstances < 1) {
			SDL_Quit();
		}
	}

	int InitSdl::nbrOfInstances = 0;

} // Namespace mw.
