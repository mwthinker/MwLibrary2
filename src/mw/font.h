#ifndef MW_FONT_H
#define MW_FONT_H

#include "initttf.h"

#include <SDL_ttf.h>
#include <string>
#include <memory>

namespace mw {

	class Font;
	typedef std::shared_ptr<Font> FontPtr;

	class Font : public InitTtf {
	public:
		// Loads a font located in file named (filename). 
		// Higher character size demands higher memory usage.
		Font(std::string filename, int characterSize);
		~Font();

		inline int getCharacterSize() const {
			return characterSize_;
		}

		// Use with care! Returns a pointer to the font data.
		inline TTF_Font* getTtfFont() const {
			return font_;
		}

	private:
		TTF_Font* font_;
		int characterSize_;
	};

} // Namespace mw.

#endif // MW_FONT_H
