#include "sprite.h"
#include "opengl.h"
#include "shader.h"

#include <SDL.h>

#include <string>
#include <functional>

namespace mw {

	namespace {

		void drawSprite(const mw::Sprite& sprite) {
			const Texture& texture = sprite.getTexture();
			if (texture.isValid()) {
				sprite.bind();
#if MW_OPENGLES2
				mw::glEnable(GL_BLEND);
				mw::glEnable(GL_TEXTURE_2D);
				mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				// Centered square in ORIGO.
				static GLfloat aVertices[] = {
					-0.5f, -0.5f,
					 0.5f, -0.5f
					-0.5f,  0.5f,
					 0.5f,  0.5f};

				// Map the sprite out from the texture.
				static GLfloat aTexCoord[] = {
					sprite.getX() / texture.getWidth(), sprite.getY() / texture.getHeight(),
					(sprite.getX() + sprite.getWidth()) / texture.getWidth(), sprite.getY() / texture.getHeight(),
					sprite.getX() / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight(),
					(sprite.getX() + sprite.getWidth()) / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight()};

				// Use the program object
				auto& shader = Shader::getDefaultShader();
				shader->glUseProgram();

				// Load the vertex data
				mw::glVertexAttribPointer(shader->getAttributeLocation(SHADER_ATTRIBUTE_VEC4_POSITION), 2, GL_FLOAT, GL_FALSE, 0, aVertices);
				mw::glVertexAttribPointer(shader->getAttributeLocation(SHADER_ATTRIBUTE_VEC2_TEXCOORD), 2, GL_FLOAT, GL_FALSE, 0, aTexCoord);
				mw::glEnableVertexAttribArray(shader->getAttributeLocation(SHADER_ATTRIBUTE_VEC4_POSITION));
				mw::glEnableVertexAttribArray(shader->getAttributeLocation(SHADER_ATTRIBUTE_VEC2_TEXCOORD));

				// Upload the attributes and draw the sprite.
				mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

				mw::glDisable(GL_TEXTURE_2D);
				mw::glDisable(GL_BLEND);
#else // MW_OPENGLES2
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
#endif // MW_OPENGLES2
				
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
