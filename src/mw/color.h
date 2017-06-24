#ifndef MW_COLOR_H
#define MW_COLOR_H

namespace mw {

	// Holds RGBA-color needed to define the color in OpenGL.
	template <typename T>
	class Color {
	public:
		Color() = default;

		Color(T red, T green, T blue, T alpha = 1) :
            red_(red), green_(green), blue_(blue), alpha_(alpha) {
		}

		Color<T> operator*(T scale) {
			return Color<T>(red_ * scale, green_ * scale, blue_ * scale, alpha_ * scale);
		}

		T red_, green_, blue_, alpha_;
	};

	template <typename T>
	Color<T> operator*(T scale, Color<T> color) {
		return Color<T>(color.red_ * scale, color.green_ * scale, color.blue_ * scale, color.alpha_ * scale);
	}

} // Namespace mw.

#endif // MW_COLOR_H
