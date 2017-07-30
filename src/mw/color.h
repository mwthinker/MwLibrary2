#ifndef MW_COLOR_H
#define MW_COLOR_H

#include "opengl.h"

namespace mw {

	// Holds RGBA-color needed to define the color in OpenGL.
	class Color {
	public:
		Color() = default;

		Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1) :
            red_(red), green_(green), blue_(blue), alpha_(alpha) {
		}

		Color operator*(GLfloat scale) {
			return Color(red_ * scale, green_ * scale, blue_ * scale, alpha_ * scale);
		}

		GLfloat red_, green_, blue_, alpha_;
	};
	
	inline Color operator*(GLfloat scale, Color color) {
		return Color(color.red_ * scale, color.green_ * scale, color.blue_ * scale, color.alpha_ * scale);
	}

} // Namespace mw.

#endif // MW_COLOR_H
