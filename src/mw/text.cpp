#include "text.h"

#include "initttf.h"
#include "font.h"
#include "sprite.h"

#include <SDL_ttf.h>

#include <string>

namespace mw {

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
