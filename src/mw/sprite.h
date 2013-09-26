#ifndef MW_SPRITE_H
#define MW_SPRITE_H

#include "texture.h"

#include <string>
#include <functional>

namespace mw {

	class Sprite {
	public:
		// Creates an empty sprite, can be used but it will draw nothing.
		Sprite();

		// Loads the image from file (image).
		Sprite(std::string image, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Creates a sprite from a texture (texture) already existing.
		// Safe to use the same texture object in other code.
		Sprite(const TexturePtr& texture);

		// Sets a texture to the sprite. Safe to use the same 
		// object texture in other code.
		void setTexture(const TexturePtr& texture);

		// Returns the sprites texture. Returns null if the sprite is
		// empty.
		TexturePtr getTexture() const;

		// Draws the image in in x = [-0.5,0.5] and y = [-0.5,0.5] by default.
		// If drawPixelSize is set to true then the image is drawn in pixel size
		// and centered in origo.
		void draw();

		// Draws the image in pixel size if the parameter drawPixelSize is true.
		// Else the image is drawn with sides with length one.
		void setDrawPixelSize(bool drawPixelSize);

		// Returns if the image is to be drawn in pixel size or not.
		bool isDrawingPixelSize();

	private:
		TexturePtr texture_;
		bool drawPixelSize_;
	};

} // Namespace mw

#endif // MW_SPRITE_H
