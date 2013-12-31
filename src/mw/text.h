#ifndef MW_TEXT_H
#define MW_TEXT_H

#include "initttf.h"
#include "font.h"
#include "sprite.h"

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
		Text(std::string text, FontPtr font);
		
		// Create a Text object with the text,font and characte size provided.
		// The text texture is created in size provided by the font but then 
		// scaled to match the provided character size.
		Text(std::string text, FontPtr font, double characterSize);
		
		~Text();

		void setText(std::string text);

		inline std::string Text::getText() const {
			return text_;
		}

		// Set the character size. The text texture is created in size 
		// provided by the font but then scaled to match the 
		// provided character size.
		inline void Text::setCharacterSize(double characterSize) {
			characterSize_ = characterSize;
		}

		// Returns the character size used for the text. May
		// or may not correspond to the internal font size.
		inline double getCharacterSize() const {
			return characterSize_;
		}

		// Returns the width of the text to be drawn.
		// (The width in openGl)
		inline double getWidth() const {
			double scale = 0;
			if (font_) {
				scale = characterSize_ / font_->getCharacterSize();
			}
			return width_ * scale;
		}

		// Returns the height of the text to be drawn.
		// (The height in openGl)
		inline double getHeight() const {
			double scale = 0;
			if (font_) {
				scale = characterSize_ / font_->getCharacterSize();
			}
			return height_ * scale;
		}

		// Returns the internal font. Can be null if no font used.
		inline FontPtr Text::getFont() const {
			return font_;
		}

		// The text is drawn, in the square [width, height] with the lower left 
		// point at origo, in OpenGl coordinate space.
		void draw() const;

	private:
		void loadText(std::string str);
		Sprite sprite_;

		std::string text_;
		double characterSize_;
		double width_, height_;
		FontPtr font_;
	};

} // Namespace mw

#endif // MW_TEXT_H
