#ifndef MW_OPENGL_H
#define MW_OPENGL_H

#if MW_OPENGL == 0
#include <SDL_opengl.h>
#elif MW_OPENGL == 1
#include <SDL_opengles.h>
#else
#include <SDL_opengles2.h>
#endif

#include <string>

namespace mw {
#if MW_OPENGL == 2
	static std::string shader_ver = ""
		"attribute vec4 a_v4Position;"
		"attribute vec4 a_v4FillColor;"
		"varying vec4 v_v4FillColor;"
		""
		"void main() {"
		"	v_v4FillColor = a_v4FillColor;"
		"	gl_Position = a_v4Position;"
		"}";

	static std::string shader_frag = ""
		"precision mediump float;"
		""
		"varying vec4 v_v4FillColor; "
		""
		"void main() {"
		"	gl_FragColor = v_v4FillColor;"
		"}";
#endif
} // Namespace mw.

#endif // MW_OPENGL_H
