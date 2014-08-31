#include "text.h"

#include "initttf.h"
#include "font.h"
#include "sprite.h"
#include "shader.h"

#include <SDL_ttf.h>

#include <string>

namespace mw {
	
	void Text::drawText() const {
		if (texture_.isValid()) {
			texture_.bind();
#if MW_OPENGLES2
			mw::glEnable(GL_BLEND);
			mw::glEnable(GL_TEXTURE_2D);
			mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Lower left corner is in ORIGO.
			GLfloat aVertices[] = {
				0, 0,
				getWidth(), 0,
				0, getHeight(),
				getWidth(), getHeight()};

			// Map the sprite out from the texture.
			GLfloat aTexCoord[] = {
				0, 0,
				1, 0,
				0, 1,
				1, 1};

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

			mw::glDisable(GL_TEXTURE_2D);
			mw::glDisable(GL_BLEND);
#else // MW_OPENGLES2
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glNormal3f(0, 0, 1);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(1, 0);
			glVertex2f(getWidth(), 0);

			glTexCoord2f(1, 1);
			glVertex2f(getWidth(), getHeight());

			glTexCoord2f(0, 1);
			glVertex2f(0, getHeight());
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
#endif // MW_OPENGLES2

		}
	}


	Text::Text() : characterSize_(0), width_(0), height_(0) {
		setText("");
	}

	Text::Text(std::string text, const Font& font) : characterSize_((float) font.getCharacterSize()), font_(font), width_(0), height_(0) {
		setText(text);
	}

	Text::Text(std::string text, const Font& font, float characterSize) : characterSize_(characterSize), font_(font), width_(0), height_(0) {
		setText(text);
	}

	void Text::setText(std::string text) {
		// Text changed? => load new textImage.
		if (text_ != text) {
			TTF_Font* font = font_.getTtfFont();
			if (font && text.size() > 0) {
				int w, h;
				if (TTF_SizeUTF8(font, text.c_str(), &w, &h) == 0) {
					float scale = characterSize_ / font_.getCharacterSize();
					width_ = (float) w;
					height_ = (float) h;
					loadText(text);
					text_ = text;
					return;
				}
			}
			text_ = text; // = "" is the same.
			width_ = 0;
			height_ = 0;
		}
	}

	void Text::draw() const {
		if (font_.getTtfFont()) {
			if (text_.size() > 0) {
				drawText();
			}
		}
	}

	void Text::loadText(std::string str) {
		if (font_.getTtfFont()) {
			if (str.size() > 0) {
				SDL_Color color = {255, 255, 255};
				SDL_Surface* surface = TTF_RenderUTF8_Blended(font_.getTtfFont(), str.c_str(), color);
				// Texture takes ownership of surface.
				texture_ = Texture(surface, []() {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				});
			}
		}
	}

} // Namespace mw.
