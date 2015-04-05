#ifndef MW_TEXT_H
#define MW_TEXT_H

#include "initttf.h"
#include "font.h"
#include "texture.h"

#include <SDL_ttf.h>

#include <string>

namespace mw {

	class Text : public InitTtf {
	public:
		// Create a empty text object.
		Text();

		// Create a Text object with the text and font provided.
		// The character size for the text is the same as the font.
		Text(std::string text, const Font& font);

		// Create a Text object with the text,font and character size provided.
		// The text texture is created in size provided by the font but then
		// scaled to match the provided character size.
		Text(std::string text, const Font& font, float characterSize);

		void setText(std::string text);

		inline std::string getText() const {
			return text_;
		}

		// Set the character size. The text texture is created in the size
		// provided by the font but then scaled to match the
		// provided character size.
		inline void setCharacterSize(float characterSize) {
			characterSize_ = characterSize;
		}

		// Return the character size used for the text. May
		// or may not correspond to the internal font size.
		inline float getCharacterSize() const {
			return characterSize_;
		}

		// Returns the width of the text to be drawn.
		// (The width in openGL).
		inline float getWidth() const {
			if (font_.getCharacterSize() < 1) {
				return 0;
			}
			return (float) (texture_.getWidth() * characterSize_ / font_.getCharacterSize());
		}

		// Return the height of the text to be drawn.
		// (The height in openGL).
		inline float getHeight() const {
			if (font_.getCharacterSize() < 1) {
				return 0;
			}
			return (float) (texture_.getHeight() * characterSize_ / font_.getCharacterSize());
		}

		// Return the current font. The font may be empty.
		inline const Font& getFont() const {
			return font_;
		}

        // Return the texture representing the text. The texture may be empty.
		inline const Texture& getTexture() const {
			return texture_;
		}

        inline void bindTexture() const {
            return texture_.bindTexture();
        }

        // Return if the underlying texture is valid.
        // I.e. the texture is in memory with width and height.
		inline bool isValid() const {
            return texture_.isValid();
		}

	private:
		bool loadTextToTexture(std::string str);

        Font font_;
		Texture texture_;
		std::string text_;
		float characterSize_;
	};

} // Namespace mw.

#endif // MW_TEXT_H
