#ifndef MW_OPENGL_H
#define MW_OPENGL_H

#if MW_OPENGLES2
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <string>

namespace mw {

#if MW_OPENGLES2
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
#endif // MW_OPENGLES2

} // Namespace mw.

#endif // MW_OPENGL_H
