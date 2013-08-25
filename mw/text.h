#ifndef MW_TEXT_H
#define MW_TEXT_H

#include "initttf.h"
#include "font.h"
#include "sprite.h"
#include "texture.h"

#include <SDL_ttf.h>
#include <string>

namespace mw {

	class Text : public InitTtf {
	public:
		Text();
		Text(std::string text, FontPtr font);
		Text(std::string text, FontPtr font, unsigned int characterSize);
		~Text();

		void setText(std::string text);
		std::string getText() const;
		void setCharacterSize(unsigned int size);
		unsigned int getCharacterSize() const;

		double getWidth() const;
		double getHeight() const;

		void draw();

	private:
		void loadText(std::string str);
		Sprite sprite_;

		std::string text_;
		unsigned int characterSize_;
		FontPtr font_;
	};

} // Namespace mw

#endif // MW_TEXT_H
