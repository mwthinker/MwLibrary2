#ifndef MW_TEXTURE_H
#define MW_TEXTURE_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <string>
#include <memory>
#include <functional>

namespace mw {

	class Texture;
	typedef std::shared_ptr<Texture> TexturePtr;

	class Texture {
	public:
		// Loads a image from a file. It stores the image in memory and no opengl
		// code are of use in the constructor (safe to call constructor in other threads).
		Texture(std::string filename, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});

		// Loads a image from data.
		Texture(int width, int height, int pixelSize, void* data, std::function<void()> filter = []() {
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

		// Is not copyable.
		Texture(const Texture&) = delete;

		// Is not copyable.
		Texture& operator=(const Texture&) = delete;

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
		// Is mutable in order for the bind() function to be const.
		// It's ok beacause the variables can be seen as cache variables.
		// So the external "constness" is preserved.
		mutable SDL_Surface* preLoadSurface_;
		mutable bool firstCallToBind_;
		mutable GLuint texture_;

		std::function<void()> filter_;
	};

} // Namespace mw.

#endif // MW_TEXTURE_H
