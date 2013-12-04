#ifndef MW_COLOR_H
#define MW_COLOR_H

#include <SDL_opengl.h>

namespace mw {

	// Holds RGB-color needed to define the color in openGl.
	class Color {
	public:
		Color() {
			red_ = 1.0;
			green_ = 1.0;
			blue_ = 1.0;
			alpha_ = 1.0;
		}

		Color(double red, double green, double blue, double alpha = 1.0) {
			red_ = red;
			green_ = green;
			blue_ = blue;
			alpha_ = alpha;
		}

		// Calls ::glColor3d(red_,green_,blue_).
		void glColor3d() const {
			::glColor3d(red_,green_,blue_);
		}

		// Calls ::glColor4d(red_,green_,blue_,alpha_).
		void glColor4d() const  {
			::glColor4d(red_,green_,blue_,alpha_);
		}

		double red_, green_, blue_, alpha_;
	};

} // Namespace mw.

#endif // MW_COLOR_H
