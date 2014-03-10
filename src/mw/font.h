#ifndef MW_FONT_H
#define MW_FONT_H

#include "initttf.h"

#include <SDL_ttf.h>
#include <string>
#include <memory>

namespace mw {

	class Font : public InitTtf {
	public:
		Font() : fontData_(std::make_shared<FontData>()) {
		}

		// Loads a font located in file named (filename). 
		// Higher character size demands higher memory usage.
		Font(std::string filename, int characterSize);

		inline int getCharacterSize() const {
			return characterSize_;
		}

		// Use with care! Returns a pointer to the font data.
		inline TTF_Font* getTtfFont() const {
			return fontData_ ? fontData_->font_ : 0;
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

} // Namespace mw.

#endif // MW_FONT_H
