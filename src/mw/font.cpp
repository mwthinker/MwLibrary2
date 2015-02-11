#include "font.h"

#include <string>
#include <iostream>

namespace mw {

	Font::Font() :
	    fontData_(std::make_shared<FontData>()),
	    characterSize_(0) {
	}

	Font::Font(const std::string& filename, int characterSize) :
	    fontData_(std::make_shared<FontData>()),
	    characterSize_(0) {

		TTF_Font* font = TTF_OpenFont(filename.c_str(), characterSize);

		if (font) {
			fontData_->font_ = font;
			characterSize_ = characterSize;
			TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
		} else {
			std::cerr << "Error font: " << TTF_GetError() << std::endl;
		}
	}

} // Namespace mw.
