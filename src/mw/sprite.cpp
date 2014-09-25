#include "sprite.h"
#include "opengl.h"
#include "shader.h"

#include <string>
#include <functional>

namespace mw {

	Sprite::Sprite() {
	}

	Sprite::Sprite(std::string image, std::function<void()> filter) : texture_(image, filter) {
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
		texture_.bindTexture();
		if (texture_.isValid()) {
#if MW_OPENGLES2
			mw::glEnable(GL_BLEND);
			mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Centered square in ORIGO.
			GLfloat aVertices[] = {
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

			// Use the program object
			auto& shader = Shader::getDefaultShader();
			shader->glUseProgram();
			mw::glUniform1f(shader->getUniformLocation(mw::SHADER_U_FLOAT_TEXTURE), 1);

			// Load the vertex data
			mw::glVertexAttribPointer(shader->getAttributeLocation(SHADER_A_VEC4_POSITION), 2, GL_FLOAT, GL_FALSE, 0, aVertices);
			mw::glVertexAttribPointer(shader->getAttributeLocation(SHADER_A_VEC2_TEXCOORD), 2, GL_FLOAT, GL_FALSE, 0, aTexCoord);
			mw::glEnableVertexAttribArray(shader->getAttributeLocation(SHADER_A_VEC4_POSITION));
			mw::glEnableVertexAttribArray(shader->getAttributeLocation(SHADER_A_VEC2_TEXCOORD));

			// Upload the attributes and draw the sprite.
			mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			mw::glDisable(GL_BLEND);
#else // MW_OPENGLES2
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glNormal3f(0, 0, 1);
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
