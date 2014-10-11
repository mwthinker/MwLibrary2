#ifndef MW_TEXT_H
#define MW_TEXT_H

#include "initttf.h"
#include "font.h"
#include "texture.h"

#include <SDL_ttf.h>

#include <string>
#include <memory>

namespace mw {

	class Text : public InitTtf {
	public:
		// Create a empty text.
		Text();

		// Create a Text object with the text and font provided.
		// The character size for the text is the same as the font.
		Text(std::string text, const Font& font);
		
		// Create a Text object with the text,font and characte size provided.
		// The text texture is created in size provided by the font but then 
		// scaled to match the provided character size.
		Text(std::string text, const Font& font, float characterSize);		

		void setText(std::string text);

		inline std::string getText() const {
			return text_;
		}

		// Set the character size. The text texture is created in size 
		// provided by the font but then scaled to match the 
		// provided character size.
		inline void setCharacterSize(float characterSize) {
			characterSize_ = characterSize;
		}

		// Returns the character size used for the text. May
		// or may not correspond to the internal font size.
		inline float getCharacterSize() const {
			return characterSize_;
		}

		// Returns the width of the text to be drawn.
		// (The width in openGl)
		inline float getWidth() const {
			float scale = 0;
			if (font_.getTtfFont()) {
				scale = characterSize_ / font_.getCharacterSize();
			}
			return width_ * scale;
		}

		// Returns the height of the text to be drawn.
		// (The height in openGl)
		inline float getHeight() const {
			float scale = 0;
			if (font_.getTtfFont()) {
				scale = characterSize_ / font_.getCharacterSize();
			}
			return height_ * scale;
		}

		// Returns the internal font. Can be null if no font used.
		inline const Font& getFont() const {
			return font_;
		}

		// The text is drawn, in the square [width, height] (i.e. in pixelsize) with the lower left 
		// point at (x,y), in OpenGl coordinate space.
		void draw(float x=0, float y=0) const;

		inline const mw::Texture& getTexture() const {
			return texture_;
		}

	private:
		void loadText(std::string str);
		void drawText(float x, float y) const;

		mw::Texture texture_;

		std::string text_;
		float characterSize_;
		float width_, height_;
		Font font_;
	};

} // Namespace mw

#endif // MW_TEXT_H
