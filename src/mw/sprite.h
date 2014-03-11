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
		Sprite(const Texture& texture);

		// Creates a sprite from a texture (texture) already existing.
		Sprite(const Texture& texture, double x, double y, double dx, double dy);

		void setTexture(const Texture& texture);

		// Sets a texture to the sprite. The sprite represents the square of the texture,
		// defined by (x,y) in the lower left postion with (dx,dy) = (width,height). 
		void setTexture(const Texture& texture, double x, double y, double dx, double dy);		

		// Returns the sprites texture.
		const Texture& getTexture() const;

		// Draws the image in in x = [-0.5,0.5] and y = [-0.5,0.5] by default.
		// If drawPixelSize is set to true then the image is drawn in pixel size
		// and centered in origo.
		void draw() const;

		// Draws the image in pixel size if the parameter drawPixelSize is true.
		// Else the image is drawn with sides with length one.
		void setDrawPixelSize(bool drawPixelSize);

		// Returns if the image is to be drawn in pixel size or not.
		bool isDrawingPixelSize() const;

	private:
		Texture texture_;
		bool drawPixelSize_;
		double x_, y_, dx_, dy_;
	};

} // Namespace mw

#endif // MW_SPRITE_H
