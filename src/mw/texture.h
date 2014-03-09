#ifndef MW_TEXTURE_H
#define MW_TEXTURE_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <string>
#include <memory>
#include <functional>

namespace mw {

	class Texture {
	public:
		// Loads a image from a file. It stores the image in memory and no opengl
		// code are of use in the constructor (safe to call constructor in other threads).
		Texture(std::string filename, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Takes over ownership of surface and is responsable of deallocation.
		// Not safe to use surface outside this class after calling the constuctor.
		Texture(SDL_Surface* surface, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Cleans the image from memory and the opengl texture from graphic memory.
		~Texture();

		// Binds the texture to the target GL_TEXTURE_2D. First call, copies 
		// the image data to graphic memory.
		void bind() const;

		// Returns the width of the image in pixels.
		int getWidth() const;

		// Returns the height of the image in pixels. 
		int getHeight() const;

		// Returns if the image is loaded correctly. It may however not be loaded
		// to graphic memory despite the result of this function.
		bool isValid() const;

	private:
		class ImageData {
		public:
			ImageData(std::function<void()> filter) : preLoadSurface_(0), texture_(0), firstCallToBind_(false), filter_(filter) {
			}

			ImageData(SDL_Surface* surface, std::function<void()> filter) : preLoadSurface_(surface), texture_(0), firstCallToBind_(false), filter_(filter) {
			}

			~ImageData();

			// Is not copyable.
			ImageData(const ImageData&) = delete;

			// Is not copyable.
			ImageData& operator=(const ImageData&) = delete;

			void bind() const;

			// Is mutable in order for the bind() function to be const.
			// It's ok beacause the variables can be seen as cache variables.
			// So the external "constness" is preserved.
			mutable SDL_Surface* preLoadSurface_;
			mutable GLuint texture_;
			mutable bool firstCallToBind_;
			std::function<void()> filter_;
		};
		
		int width_, height_;
		bool valid_;
		std::shared_ptr<ImageData> imageData_;
	};

} // Namespace mw.

#endif // MW_TEXTURE_H
