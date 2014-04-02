#include "sprite.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <string>
#include <functional>

namespace mw {

	namespace {

		void drawSprite(const mw::Sprite& sprite) {
			const Texture& texture = sprite.getTexture();
			if (texture.isValid()) {
				sprite.bind();

				glEnable(GL_BLEND);
				glEnable(GL_TEXTURE_2D);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glNormal3f(0, 0, 1);
				glBegin(GL_QUADS);
				glTexCoord2f(sprite.getX() / texture.getWidth(), sprite.getY() / texture.getHeight());
				glVertex2f(-0.5, -0.5);

				glTexCoord2f((sprite.getX() + sprite.getWidth()) / texture.getWidth(), sprite.getY() / texture.getHeight());
				glVertex2f(0.5, -0.5);

				glTexCoord2f((sprite.getX() + sprite.getWidth()) / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight());
				glVertex2f(0.5, 0.5);

				glTexCoord2f(sprite.getX() / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight());
				glVertex2f(-0.5, 0.5);
				glEnd();

				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			}
		}

	}

	Sprite::Sprite() : drawFunc_(std::bind(drawSprite, std::placeholders::_1)) {
	}

	Sprite::Sprite(std::string image, std::function<void()> filter) : texture_(image, filter), drawFunc_(std::bind(drawSprite, std::placeholders::_1)) {
		x_ = 0;
		y_ = 0;
		dx_ = (float) texture_.getWidth();
		dy_ = (float) texture_.getHeight();
	}

	// Load a image from file.
	Sprite::Sprite(std::string image, std::function<void(const mw::Sprite& sprite)> draw, std::function<void()> filter) : texture_(image, filter), drawFunc_(draw) {
		x_ = 0;
		y_ = 0;
		dx_ = (float) texture_.getWidth();
		dy_ = (float) texture_.getHeight();
	}

	Sprite::Sprite(const Texture& texture) : texture_(texture), drawFunc_(std::bind(drawSprite, std::placeholders::_1)) {
		x_ = 0;
		y_ = 0;
		dx_ = (float) texture.getWidth();
		dy_ = (float) texture.getHeight();
	}

	Sprite::Sprite(const Texture& texture, std::function<void(const mw::Sprite& sprite)> draw) : texture_(texture), drawFunc_(draw) {
		x_ = 0;
		y_ = 0;
		dx_ = (float) texture.getWidth();
		dy_ = (float) texture.getHeight();
	}

	Sprite::Sprite(const Texture& texture, float x, float y, float dx, float dy) : texture_(texture), drawFunc_(std::bind(drawSprite, std::placeholders::_1)), x_(x), y_(y), dx_(dx), dy_(dy) {
		x_ = x;
		y_ = y;
		dx_ = dx;
		dy_ = dy;
	}

	// Create a sprite from a texture already existing.
	Sprite::Sprite(const Texture& texture, std::function<void(const mw::Sprite& sprite)> draw, float x, float y, float dx, float dy) : texture_(texture), drawFunc_(draw) {
		x_ = x;
		y_ = y;
		dx_ = dx;
		dy_ = dy;
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

	void Sprite::draw() const {
		drawFunc_(*this);
	}

	void Sprite::setDrawFunction(const std::function<void(const mw::Sprite& sprite)>& drawFunc) {
		drawFunc_ = drawFunc;
	}

} // Namespace mw.
