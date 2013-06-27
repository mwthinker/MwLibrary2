#include "font.h"

#include <string>

namespace mw {

	Font::Font(std::string filename, unsigned int characterSize) {
		characterSize_ = characterSize;
		font_ = TTF_OpenFont(filename.c_str(),characterSize);

		if (font_ == 0) { // 0 = null
			std::cout << "Error font" << std::endl;
			//throw 1;
		}
	}

	Font::~Font() {
		if (font_ != 0) {
			TTF_CloseFont(font_);
		}
	}
	
} // namespace mw