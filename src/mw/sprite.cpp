#include "sprite.h"
#include "opengl.h"

#include <string>
#include <functional>

namespace mw {

	Sprite::Sprite() : x_(0), y_(0), dx_(0), dy_(0) {
	}

	Sprite::Sprite(std::string image, std::function<void()> filter) :
		texture_(image, filter) {
		x_ = 0;
		y_ = 0;
		dx_ = (float) texture_.getWidth();
		dy_ = (float) texture_.getHeight();
	}

	Sprite::Sprite(const Texture& texture) :
		texture_(texture),
		x_(0),
		y_(0),
		dx_((float) texture.getWidth()),
		dy_((float) texture.getHeight()) {

	}

	Sprite::Sprite(const Texture& texture, float x, float y, float dx, float dy) :
		texture_(texture),
		x_(x),
		y_(y),
		dx_(dx),
		dy_(dy) {

	}

	void Sprite::setTexture(const Texture& texture) {
		texture_ = texture;
		x_ = 0;
		y_ = 0;
		dx_ = (float) texture.getWidth();
		dy_ = (float) texture.getHeight();
	}

	void Sprite::setTexture(const Texture& texture, float x, float y, float dx, float dy) {
		texture_ = texture;
		x_ = x;
		y_ = y;
		dx_ = dx;
		dy_ = dy;
	}

} // Namespace mw.
