#ifndef MW_COLOR_H
#define MW_COLOR_H

#include "opengl.h"

namespace mw {

	// Holds RGB-color needed to define the color in openGl.
	class Color {
	public:
		Color() {
			red_ = 1.f;
			green_ = 1.f;
			blue_ = 1.f;
			alpha_ = 1.f;
		}

		Color(float red, float green, float blue, float alpha = 1.f) {
			red_ = red;
			green_ = green;
			blue_ = blue;
			alpha_ = alpha;
		}

		// Calls ::glColor3d(red_,green_,blue_).
		void glColor3f() const {
			::glColor3d(red_,green_,blue_);
		}

		// Calls ::glColor4d(red_,green_,blue_,alpha_).
		void glColor4f() const  {
			::glColor4f(red_,green_,blue_,alpha_);
		}

		float red_, green_, blue_, alpha_;
	};

} // Namespace mw.

#endif // MW_COLOR_H
