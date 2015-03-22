#ifndef MW_OPENGL_H
#define MW_OPENGL_H

#include <GL/glew.h>

namespace mw {

// Function checkGlError() prints all OpenGL errors during debug mode.
#if _DEBUG

	// Print all OpenGL errors.
	// Call check_gl_error instead if the error checking only should be in debug mode.
	void _checkGlError(const char* file, int line);

#define checkGlError() _checkGlError(__FILE__,__LINE__)
#else // _DEBUG

	inline void _empty() {}

#define checkGlError() _empty()
#endif // _DEBUG

} // Namespace mw.

#endif // MW_OPENGL_H
