#include "text.h"

#include "initttf.h"
#include "font.h"
#include "sprite.h"
#include "defaultshader.h"

#include <SDL_ttf.h>

#include <string>

namespace mw {
	
	void Text::drawText(float x, float y) const {
		if (texture_.isValid()) {
			texture_.bindTexture();
#if MW_OPENGLES2
			mw::glEnable(GL_BLEND);
			mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Lower left corner is in ORIGO.
			GLfloat aPos[] = {
				x, y,
				x + getWidth(), y,
				x, getHeight() + y,
				x + getWidth(), getHeight() + y};

			// Map the sprite out from the texture.
			GLfloat aTex[] = {
				0, 0,
				1, 0,
				0, 1,
				1, 1};

			// Use the program object
			// Use the program object
			const DefaultShader& shader = DefaultShader::get();
			shader.glUseProgram();
			shader.setGlTextureU(true);

			// Set the vertex pointer.
			shader.setGlPosA(2, aPos);
			shader.setGlTexA(2, aTex);

			// Upload the attributes and draw the sprite.
			mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			mw::glDisable(GL_BLEND);

#else // MW_OPENGLES2
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(x, y);

			glTexCoord2f(1, 0);
			glVertex2f(x + getWidth(), y);

			glTexCoord2f(1, 1);
			glVertex2f(x + getWidth(), y + getHeight());

			glTexCoord2f(0, 1);
			glVertex2f(x, y + getHeight());
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
#endif // MW_OPENGLES2
			checkGlError();
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

	void Text::draw(float x, float y) const {
		if (font_.getTtfFont()) {
			if (text_.size() > 0) {
				drawText(x, y);
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
