#include "opengl.h"

#include <iostream>
#include <string>

namespace mw {

	namespace {

		std::string errorString(GLenum error) {
			switch (error) {
				case GL_INVALID_ENUM:
					return "GL_INVALID_ENUM";
				case GL_INVALID_VALUE:
					return "GL_INVALID_VALUE";
				case GL_INVALID_OPERATION:
					return "GL_INVALID_OPERATION";
				case GL_STACK_UNDERFLOW:
					return "GL_STACK_UNDERFLOW";
				case GL_OUT_OF_MEMORY:
					return "GL_OUT_OF_MEMORY";
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					return "GL_INVALID_FRAMEBUFFER_OPERATION";
				case GL_CONTEXT_LOST:
					return "GL_CONTEXT_LOST";
				case GL_TABLE_TOO_LARGE:
					return "GL_TABLE_TOO_LARGE";
			}
			return "";
		}
	}

	void _checkGlError(const char *file, int line) {
		while (GLenum error = glGetError()) {
			std::cerr << "OpenGl error: " << error << "=" << errorString(error) << " - " << file << ":" << line << std::endl;
		}
	}

} // Namespace mw.
