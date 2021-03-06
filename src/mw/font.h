#ifndef MW_FONT_H
#define MW_FONT_H

#include "initttf.h"

#include <SDL_ttf.h>

#include <string>
#include <memory>

namespace mw {

	class Font : public InitTtf {
	public:
		// Creates an empty font.
		Font();

		bool operator==(const Font& font) const;

		bool operator!=(const Font& font) const;

		// Load the font located in the file named (filename).
		// Higher character size demands higher memory usage.
		Font(const std::string& filename, int characterSize);

		int getCharacterSize() const {
			return characterSize_;
		}

		// Use with care! Return a pointer to the font data.
		inline TTF_Font* getTtfFont() const {
			return fontData_->font_;
		}

	private:
		class FontData {
		public:
			FontData() : font_(0) {
			}

			~FontData() {
				if (font_ != 0) {
					TTF_CloseFont(font_);
				}
			}

			TTF_Font* font_;
		};

		std::shared_ptr<FontData> fontData_;
		int characterSize_;
	};

	inline bool Font::operator==(const Font& font) const {
		return fontData_ == font.fontData_;
	}

	inline bool Font::operator!=(const Font& other) const {
		return !(*this == other);
	}

} // Namespace mw.

#endif // MW_FONT_H
