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

		// Cleens the image from memory and the opengl texture from graphic memory.
		~Texture();

		// Binds the texture to the target GL_TEXTURE_2D. First call, copies 
		// the image data to graphic memory.
		void bind();

		// Returns the width of the image in pixels.
		int getWidth() const;

		// Returns the height of the image in pixels. 
		int getHeight() const;

		// Use with care. Gets a copy of the underlaying surface.
		SDL_Surface* getSdlSurface() const;

		// Returns if the image is loadad correctly. It may however not be loaded
		// to graphic memory despite the result of this function.
		bool isValid() const;

	private:
		Texture(const Texture&) {
			// Not to be used. Is not copyable.
		}

		Texture& operator=(const Texture&) {
			// Not to be used. Is not copyable.
			return *this;
		}

		// Is called when the opengl context need to be loaded.
		void loadToVideo();

		GLuint texture_;
		SDL_Surface* preLoadSurface_;
		std::function<void()> filter_;
	};

} // Namespace mw.

#endif // MW_TEXTURE_H
