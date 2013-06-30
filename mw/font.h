#ifndef MW_FONT_H
#define MW_FONT_H

#include "initttf.h"

#include <SDL_ttf.h>

#include <string>
#include <memory>

namespace mw {

	// Simple wrapper around TTF_Font.
	class Font : public InitTtf {
	public:

		// Loads a font located in file named (filename). The font is created to be in
		// size (characterSize) default 30 size. Higher size demands higher memory usage.
		Font(std::string filename, unsigned int characterSize = 30);
		~Font();

		inline unsigned int getCharacterSize() const {
			return characterSize_;
		}

		// Use with care. Gets the pointer to the underlying sdl font.
		inline TTF_Font* getSdlFont() const {
			return font_;
		}
	private:
		Font(const Font&) {
			// Not to be used. Is not copyable.
		}

		Font& operator=(const Font&) {
			// Not to be used. Is not copyable.
			return *this;
		}

		TTF_Font* font_;
		unsigned int characterSize_;

		friend class Text;
	};

	typedef std::shared_ptr<Font> FontPtr;

} // namespace mw

#endif // MW_FONT_H
