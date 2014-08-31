#include "color.h"

namespace mw {

	Color::Color() {
		red_ = 1.f;
		green_ = 1.f;
		blue_ = 1.f;
		alpha_ = 1.f;
	}

	Color::Color(float red, float green, float blue, float alpha) {
		red_ = red;
		green_ = green;
		blue_ = blue;
		alpha_ = alpha;
	}

} // Namespace mw.
