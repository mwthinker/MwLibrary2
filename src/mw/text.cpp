#include "text.h"

#include "initttf.h"
#include "font.h"
#include "texture.h"

#include <SDL_ttf.h>

#include <string>

namespace mw {

	Text::Text() : characterSize_(0), width_(0), height_(0) {
		setText("");
	}

	Text::Text(std::string text, FontPtr font) : characterSize_(font->getCharacterSize()), font_(font), width_(0), height_(0) {
		setText(text);
    }

	Text::Text(std::string text, FontPtr font, double characterSize) : characterSize_(characterSize), font_(font), width_(0), height_(0) {
		setText(text);
    }

    Text::~Text() {
    }

    void Text::setText(std::string text) {
		// Text changed? => load new textImage.
		if (text_ != text) {
			if (font_ && text.size() > 0) {
				int w, h;
				if (TTF_SizeUTF8(font_->getTtfFont(), text.c_str(), &w, &h) == 0) {
					double scale = characterSize_ / font_->getCharacterSize();
					width_ = w;
					height_ = h;
					loadText(text);
					text_ = text;
					return;
				}
			}
			width_ = 0;
			height_ = 0;
		}
    }
	
    void Text::draw() const {
		if (font_) {
			if (text_.size() > 0) {
				glPushMatrix();
				glScaled(getWidth(), getHeight(), 1.0);
				glTranslated(0.5,0.5,0.0);
				sprite_.draw();
				glPopMatrix();
			}
		}
    }

    void Text::loadText(std::string str) {
		if (font_) {
			if (str.size() > 0) {
				SDL_Color color = {255,255,255};
				SDL_Surface* surface = TTF_RenderUTF8_Blended(font_->getTtfFont(), str.c_str(), color);
				// Texture takes ownership of surface.
				TexturePtr texture = TexturePtr(new Texture(surface,[]() {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				}));
				sprite_.setTexture(texture);
			}
		}
    }

} // Namespace mw.
