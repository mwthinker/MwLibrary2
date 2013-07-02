#include "initsdl.h"

#include <iostream>

#include <SDL.h>

namespace mw {

	InitSdl::InitSdl() {
		if (nbrOfInstances_ < 1) {
			if ( SDL_Init(SDL_INIT_EVERYTHING) ) {
				std::cout << "Unable to init SDL: " << SDL_GetError() << "\n";
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
