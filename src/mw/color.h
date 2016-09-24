#ifndef MW_COLOR_H
#define MW_COLOR_H

namespace mw {

	// Holds RGBA-color needed to define the color in OpenGL.
	template <typename T>
	class Color {
	public:
		inline Color() {
		}

		inline Color(T red, T green, T blue, T alpha = 1) :
            red_(red), green_(green), blue_(blue), alpha_(alpha) {
		}

		T red_, green_, blue_, alpha_;
	};

} // Namespace mw.

#endif // MW_COLOR_H
