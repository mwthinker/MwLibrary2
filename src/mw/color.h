#ifndef MW_COLOR_H
#define MW_COLOR_H

#include "opengl.h"

namespace mw {

	// Holds RGBA-color needed to define the color in OpenGL.
	class Color {
	public:
		inline Color() {
		}

		inline Color(float red, float green, float blue, float alpha = 1.f) :
            red_(red), green_(green), blue_(blue), alpha_(alpha) {
		}

		float red_, green_, blue_, alpha_;
	};

} // Namespace mw.

#endif // MW_COLOR_H
