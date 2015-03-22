#ifndef MW_TEXTURE_H
#define MW_TEXTURE_H

#include "opengl.h"

#include <SDL_image.h>

#include <string>
#include <memory>
#include <functional>
#include <algorithm>

namespace mw {

	namespace helper {

		// Assumes that the surface is in RGBA.		
		void flipVertical(SDL_Surface* surface);

		SDL_Surface* createSurface(int w, int h);

	}

	class Texture {
	public:
		friend class TextureAtlas;

		// Empty texture. Does nothing.
		Texture();

		// Loads a image from a file. It stores the image in memory and no opengl
		// code are of use in the constructor (safe to call constructor in other threads).
		explicit Texture(std::string filename, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// The texture object takes over the ownership of the surface and is responsible of deallocation.
		// Not safe to use surface outside this class after calling the constuctor.
		explicit Texture(SDL_Surface* surface, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Create a empty texture.
		explicit Texture(int width, int height, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Binds the texture to the target. First call, copies 
		// the image data to graphic memory.
		void bindTexture() const;

		// Return the width of the image in pixels.
		inline int getWidth() const {
			return width_;
		}

		// Return the height of the image in pixels. 
		int getHeight() const {
			return height_;
		}

		// Return true if the image is loaded correctly. It may however not been loaded
		// to graphic memory despite the result of this function.
		bool isValid() const {
			return valid_;
		}

	private:
		class ImageData {
		public:
			ImageData(std::function<void()> filter);

			ImageData(SDL_Surface* surface, std::function<void()> filter);

			~ImageData();

			// Is not copyable.
			ImageData(const ImageData&) = delete;

			// Is not copyable.
			ImageData& operator=(const ImageData&) = delete;

			void loadImageToGraphic() const;

			// Is mutable in order for the bind() function to be const.
			// It's ok beacause the variables can be seen as cache variables.
			// So the external "constness" is preserved.
			mutable SDL_Surface* preLoadSurface_;
			mutable GLuint texture_;
			std::function<void()> filter_;
			char windowInstance_;
		};
		
		mutable bool firstCallBind_;
		mutable GLuint texture_;
		int width_, height_;
		bool valid_;
		std::shared_ptr<ImageData> imageData_;
	};

} // Namespace mw.

#endif // MW_TEXTURE_H
