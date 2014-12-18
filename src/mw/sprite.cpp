#include "sprite.h"
#include "opengl.h"
#include "defaultshader.h"

#include <string>
#include <functional>

namespace mw {

	Sprite::Sprite() {
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

	void Sprite::draw() const {
		if (texture_.isValid()) {
			texture_.bindTexture();
#if MW_OPENGLES2
			mw::glEnable(GL_BLEND);
			mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Centered square in ORIGO.
			GLfloat aPosCoords[] = {
				-0.5f, -0.5f,
				0.5f, -0.5f,
				-0.5f, 0.5f,
				0.5f, 0.5f};

			// Map the sprite out from the texture.
			GLfloat aTexCoord[] = {
				x_ / texture_.getWidth(), y_ / texture_.getHeight(),
				(x_ + dx_) / texture_.getWidth(), y_ / texture_.getHeight(),
				x_ / texture_.getWidth(), (y_ + dy_) / texture_.getHeight(),
				(x_ + dx_) / texture_.getWidth(), (y_ + dy_) / texture_.getHeight()};

			// Use the program object.
			const DefaultShader& shader = DefaultShader::get();
			shader.glUseProgram();
			shader.setGlTextureU(true);

			// Set the vertex pointer.
			shader.setGlPosA(2, aPosCoords);
			shader.setGlTexA(2, aTexCoord);

			// Upload the attributes and draw the sprite.
			mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			mw::glDisable(GL_BLEND);
#else // MW_OPENGLES2
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			glTexCoord2f(x_/ texture_.getWidth(), y_ / texture_.getHeight());
			glVertex2f(-0.5, -0.5);

			glTexCoord2f((x_ + dx_) / texture_.getWidth(), y_ / texture_.getHeight());
			glVertex2f(0.5, -0.5);

			glTexCoord2f((x_ + dx_) / texture_.getWidth(), (y_ + dy_) / texture_.getHeight());
			glVertex2f(0.5, 0.5);

			glTexCoord2f(x_ / texture_.getWidth(), (y_ + dy_) / texture_.getHeight());
			glVertex2f(-0.5, 0.5);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
#endif // MW_OPENGLES2
			checkGlError();
		}
	}

} // Namespace mw.
