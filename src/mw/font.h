#ifndef MW_FONT_H
#define MW_FONT_H

#include "initttf.h"

#include <SDL_ttf.h>

#include <string>
#include <iostream>
#include <memory>

namespace mw {

	class Font;
	typedef std::shared_ptr<Font> FontPtr;

	class Font : public InitTtf {
	public:

		// Loads a font located in file named (filename). The font is created to be in
		// size (characterSize) default 30 size. Higher size demands higher memory usage.
		Font(std::string filename, unsigned int characterSize = 30);
		~Font();

		inline unsigned int getCharacterSize() const {
			return characterSize_;
		}

		// Use with care! Gets a pointer to the font data.
		inline TTF_Font* getTtfFont() const {
			font_;
		}

	private:
		TTF_Font* font_;
		unsigned int characterSize_;

		friend class Text;
	};

} // Namespace mw.

#endif // MW_FONT_H
