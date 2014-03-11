#include "sprite.h"

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

namespace mw {

	Sprite::Sprite() : drawPixelSize_(false) {
	}

	Sprite::Sprite(std::string image, std::function<void()> filter) : texture_(image, filter), drawPixelSize_(false) {
		drawPixelSize_ = false;
		x_ = 0;
		y_ = 0;
		dx_ = texture_.getWidth();
		dy_ = texture_.getHeight();
	}

	Sprite::Sprite(const Texture& texture) : texture_(texture), drawPixelSize_(false) {
		texture_ = texture;
		drawPixelSize_ = false;
		x_ = 0;
		y_ = 0;
		dx_ = texture.getWidth();
		dy_ = texture.getHeight();
	}

	Sprite::Sprite(const Texture& texture, double x, double y, double dx, double dy) : texture_(texture), drawPixelSize_(false), x_(x), y_(y), dx_(dx), dy_(dy) {
		texture_ = texture;
		drawPixelSize_ = false;
		x_ = 0;
		y_ = 0;
		dx_ = texture.getWidth();
		dy_ = texture.getHeight();
	}

	void Sprite::setTexture(const Texture& texture) {
		texture_ = texture;
		x_ = 0;
		y_ = 0;
		dx_ = texture.getWidth();
		dy_ = texture.getHeight();
	}

	void Sprite::setTexture(const Texture& texture, double x, double y, double dx, double dy) {
		texture_ = texture;
		x_ = x;
		y_ = y;
		dx_ = dx;
		dy_ = dy;
	}

	const Texture& Sprite::getTexture() const {
		return texture_;
	}

	void Sprite::draw() const {
		if (texture_.isValid()) {
			texture_.bind();

			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPushMatrix();

			if (drawPixelSize_) {
				glScaled(texture_.getWidth(), texture_.getHeight(), 1);
			}

			// Inverts the image. Y-is "up" for the window and x is "right".
			glScaled(1, -1, 1);

			glNormal3d(0, 0, 1);
			glBegin(GL_QUADS);
			glTexCoord2d(x_ / texture_.getWidth(), y_ / texture_.getHeight());
			glVertex2d(-0.5, -0.5);

			glTexCoord2d((x_ + dx_) / texture_.getWidth(), y_ / texture_.getHeight());
			glVertex2d(0.5, -0.5);

			glTexCoord2d((x_ + dx_) / texture_.getWidth(), (y_ + dy_) / texture_.getHeight());
			glVertex2d(0.5, 0.5);

			glTexCoord2d(x_ / texture_.getWidth(), (y_ + dy_) / texture_.getHeight());
			glVertex2d(-0.5, 0.5);
			glEnd();

			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}

	void Sprite::setDrawPixelSize(bool drawPixelSize) {
		drawPixelSize_ = drawPixelSize;
	}

	bool Sprite::isDrawingPixelSize() const {
		return drawPixelSize_;
	}

} // Namespace mw.
