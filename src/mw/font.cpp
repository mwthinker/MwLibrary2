#include "font.h"

#include <string>
#include <iostream>

namespace mw {

	Font::Font(std::string filename, int characterSize) {
		characterSize_ = characterSize;
		TTF_Font* font = TTF_OpenFont(filename.c_str(), characterSize);

		if (font) {
			fontData_ = std::make_shared<FontData>();
			fontData_->font_ = font;
		} else {
			std::cerr << "Error font" << std::endl;
		}
	}
	
} // Namespace mw.
