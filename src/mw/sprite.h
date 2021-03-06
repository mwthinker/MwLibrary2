#ifndef MW_SPRITE_H
#define MW_SPRITE_H

#include "texture.h"

#include <string>
#include <functional>

namespace mw {

	class Sprite {
	public:
		// Create an empty sprite, but it will draw nothing.
		Sprite();

		// Load an image from file.
		explicit Sprite(std::string image, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Create a sprite from a texture already existing.
		Sprite(const Texture& texture);

		// Create a sprite from a texture already existing.
		Sprite(const Texture& texture, float x, float y, float dx, float dy);

		void setTexture(const Texture& texture);

		// Set a texture to the sprite. The sprite represents the square of the texture,
		// defined by (x,y) in the lower left postion with (dx,dy) = (width,height).
		void setTexture(const Texture& texture, float x, float y, float dx, float dy);

		// Return the sprite texture.
		const Texture& getTexture() const {
			return texture_;
		}

		void bindTexture() const {
			texture_.bindTexture();
		}

		// Return the lower left x position of the image drawn.
		float getX() const {
			return x_;
		}

		// Return the lower left y position of the image drawn.
		float getY() const {
			return y_;
		}

		// Return the width of the image.
		float getWidth() const {
			return dx_;
		}

		// Return the height of the image.
		float getHeight() const {
			return dy_;
		}

	private:
		Texture texture_;
		float x_, y_, dx_, dy_;
	};

} // Namespace mw.

#endif // MW_SPRITE_H
