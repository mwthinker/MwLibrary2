#include "initttf.h"

#include <SDL_ttf.h>

namespace mw {

	InitTtf::InitTtf() {
		if (nbrOfInstances_ < 1) {
			if (!TTF_WasInit() && TTF_Init() == -1) {
				// Error.
			}
		}
		++nbrOfInstances_;
	}

	InitTtf::~InitTtf() {
		--nbrOfInstances_;
		if (TTF_WasInit() && nbrOfInstances_ < 1) {
			TTF_Quit();
		}
	}	

	int InitTtf::nbrOfInstances_ = 0;

} // Namespace mw.
