#ifndef MW_SPRITE_H
#define MW_SPRITE_H

#include "texture.h"

#include <string>
#include <functional>

namespace mw {

	class Sprite {
	public:
		// Create a empty sprite, but it will draw nothing.
		Sprite();

		// Load a image from file.
		Sprite(std::string image, std::function<void()> filter = []() {
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
		const Texture& getTexture() const;

		// Draw the image in in x = [-0.5,0.5] and y = [-0.5,0.5] by default.
		// If drawPixelSize is set to true then the image is drawn in pixel size
		// and centered in origo.
		void draw() const;

		// Draws the image in pixel size if the parameter drawPixelSize is true.
		// Else the image is drawn with sides with length one.
		void setDrawPixelSize(bool drawPixelSize);

		// Return if the image is to be drawn in pixel size or not.
		bool isDrawingPixelSize() const;

		// Return the lower left x position of the image drawn.
		inline float getX() const {
			return x_;
		}

		// Return the lower left y position of the image drawn.
		inline float getY() const {
			return x_;
		}
		
		// Return the width of the image.
		inline float getWidth() const {
			return dx_;
		}
		
		// Return the height of the image.
		inline float getHeight() const {
			return dy_;
		}

	private:
		Texture texture_;
		bool drawPixelSize_;
		float x_, y_, dx_, dy_;
	};

} // Namespace mw.

#endif // MW_SPRITE_H
