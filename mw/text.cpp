#include "text.h"

#include "initttf.h"
#include "font.h"

#include <SDL_ttf.h>
#include <string>

#include <memory>

namespace mw {

	Text::Text() {
	}

    Text::Text(std::string text, FontPtr font) : font_(font) {
        text_ = text;
        loadText(text_);
        characterSize_ = font->getCharacterSize();
    }

	Text::Text(std::string text, FontPtr font, unsigned int characterSize) : font_(font) {
        text_ = text;
        loadText(text_);
        characterSize_ = characterSize;
    }

    Text::~Text() {
    }

    void Text::setText(std::string text) {
		// Text changed? => load new textImage.
        if (text_ != text) {
            loadText(text);
            text_ = text;
        }
    }

    std::string Text::getText() const {
        return text_;
    }

    void Text::setCharacterSize(unsigned int size) {
        characterSize_ = size;
    }

    unsigned int Text::getCharacterSize() const {
        return characterSize_;
    }

	// Returns the width of the text to be drawn. (size in openGl
    double Text::getWidth() const {
		if (font_ && text_.size() > 0) {
			double scale = characterSize_*1.0/font_->getCharacterSize();
			TexturePtr texture = sprite_.getTexture();
			return scale * texture->getWidth();
		}
		return 0.0;
    }

	// Returns the height of the text to be drawn.
    double Text::getHeight() const {
		if (font_ && text_.size() > 0) {
			TexturePtr texture = sprite_.getTexture();
			double scale = characterSize_*1.0/font_->getCharacterSize();
			return scale*texture->getHeight();
		}
		return 0.0;
    }

    void Text::draw() {
		if (font_) {
			if (text_.size() > 0) {
				glPushMatrix();
				double scale = characterSize_*1.0/font_->getCharacterSize();
				TexturePtr texture = sprite_.getTexture();
				glScaled(scale * texture->getWidth(),scale * texture->getHeight(),1.0);
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
				SDL_Surface* surface = TTF_RenderText_Blended(font_->font_, str.c_str(), color);
				// texture_ takes ownership of surface
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
