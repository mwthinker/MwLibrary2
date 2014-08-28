#include "color.h"
#include "sprite.h"
#include "opengl.h"

namespace mw {

#if MW_OPENGLES2
	std::string mw::Color::SHADER_UNIFORM_VEC4_COLOR = "uColor";
#endif // MW_OPENGLES2

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

	// Calls ::glColor3d(red_,green_,blue_).
	void Color::glColor3f() const {
#if MW_OPENGLES2
		mw::glUniform4f(Sprite::getShaderPtr()->getUniformLocation(Color::SHADER_UNIFORM_VEC4_COLOR), red_, green_, blue_, 1);
#else // MW_OPENGLES2
		::glColor3d(red_,green_,blue_);
#endif // MW_OPENGLES2
	}

	// Calls ::glColor4d(red_,green_,blue_,alpha_).
	void Color::glColor4f() const {
#if MW_OPENGLES2
		mw::glUniform4f(Sprite::getShaderPtr()->getUniformLocation(Color::SHADER_UNIFORM_VEC4_COLOR), red_, green_, blue_, alpha_);
#else // MW_OPENGLES2
		::glColor4f(red_,green_,blue_,alpha_);
#endif // MW_OPENGLES2
	}

} // Namespace mw.

