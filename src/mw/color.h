#ifndef MW_COLOR_H
#define MW_COLOR_H

#include "opengl.h"

#if MW_OPENGLES2
#include <string>
#endif // MW_OPENGLES2

namespace mw {

	// Holds RGB-color needed to define the color in openGl.
	class Color {
	public:
		Color();

		Color(float red, float green, float blue, float alpha = 1.f);

		// Calls ::glColor3d(red_,green_,blue_).
		void glColor3f() const;

		// Calls ::glColor4d(red_,green_,blue_,alpha_).
		void glColor4f() const;

		float red_, green_, blue_, alpha_;
#if MW_OPENGLES2
		static std::string SHADER_UNIFORM_VEC4_COLOR;
#endif // MW_OPENGLES2
	};

} // Namespace mw.

#endif // MW_COLOR_H
