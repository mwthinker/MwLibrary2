#include "opengl.h"

#include <iostream>

namespace mw {

	void _checkGlError(const char *file, int line) {		
		while (GLenum error = glGetError()) {
			std::cerr << "OpenGl error: " << error << " - " << file << ":" << line << std::endl;
		}
	}

} // Namespace mw.
