#ifndef MW_COLOR_H
#define MW_COLOR_H

#include "opengl.h"

namespace mw {

	// Holds RGB-color needed to define the color in openGl.
	class Color {
	public:
		Color();

		Color(float red, float green, float blue, float alpha = 1.f);

#ifndef MW_OPENGLES2
		inline void glColor3f() const {
			::glColor3f(red_, green_, blue_);
		}

		inline void glColor4f() const {
			::glColor4f(red_, green_, blue_, alpha_);
		}
#endif // MW_OPENGLES2

		float red_, green_, blue_, alpha_;
	};

} // Namespace mw.

#endif // MW_COLOR_H
