#include "font.h"

#include <string>
#include <iostream>

namespace mw {

	Font::Font() : fontData_(std::make_shared<FontData>()) {
	}

	Font::Font(std::string filename, int characterSize) : fontData_(std::make_shared<FontData>()) {
		characterSize_ = characterSize;
		TTF_Font* font = TTF_OpenFont(filename.c_str(), characterSize);

		if (font) {
			fontData_->font_ = font;
		} else {
			std::cerr << "Error font" << std::endl;
		}
	}
	
} // Namespace mw.
