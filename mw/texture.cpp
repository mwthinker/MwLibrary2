#include "texture.h"
#include "window.h"

#include <SDL_image.h>
#include <SDL_opengl.h>

#include <iostream>

namespace mw {

	namespace {

		// Creates and returns a opengl texture from the surface provided.
		bool SdlGlLoadTexture(SDL_Surface* const surface, GLuint& textureId) {
			glGenTextures(1, &textureId);

			if (glGetError() == GL_NO_ERROR) {
				int mode = GL_RGB;
				if (surface->format->BytesPerPixel == 4) {
					mode = GL_RGBA;
				}
				glBindTexture(GL_TEXTURE_2D, textureId);
				glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
				return true;
			}

			return false;
		}
	}

	Texture::Texture(std::string filename) : loadedToVideo_(false) {
		preLoadSurface_ = IMG_Load(filename.c_str());
		if (preLoadSurface_ == 0) {
			std::cout << "\nImage " << filename << " failed to load: " << IMG_GetError();			
		}
	}

	Texture::Texture(int width, int height, int pixelSize, void* data) {
		preLoadSurface_ = SDL_CreateRGBSurfaceFrom(data,
			width, height,
			pixelSize * 8,
			pixelSize,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			0xff000000,
			0x00ff0000,
			0x0000ff00,
			0x000000ff,
#else
			0x000000ff,
			0x0000ff00,
			0x00ff0000,
			0xff000000
#endif
			);

		loadedToVideo_ = false;
	}

	SDL_Surface* Texture::getSdlSurface() const {
		return preLoadSurface_;
	}

	Texture::~Texture() {
		if (loadedToVideo_) {
			// Is called if the opengl texture is valid and therefore need to be cleaned up.
			glDeleteTextures(1,&texture_);
		}

		// Safe to pass null.
		SDL_FreeSurface(preLoadSurface_);
	}

	void Texture::bind() {
		bind([](){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});
	}

	void Texture::bind(std::function<void()> filter) {
		if (!loadedToVideo_ && preLoadSurface_ != nullptr) {
			// Loads to video memory if current texture not valid.
			loadToVideo();
			if (loadedToVideo_) {
				filter();
			}
		} else {
			if (loadedToVideo_) {
				glBindTexture(GL_TEXTURE_2D, texture_);
			}
		}
	}

	int Texture::getWidth() const {
		return preLoadSurface_->w;
	}

	int Texture::getHeight() const {
		return preLoadSurface_->h;
	}

	// class Texture takes over ownership of surface and is responsable of deallocation.
	// Not safe to use surface outside this class after calling the constuctor.
	Texture::Texture(SDL_Surface* surface) : preLoadSurface_(surface), loadedToVideo_(false) {
	}

	// Is called when the opengl context need to be loaded.
	void Texture::loadToVideo() {
		if (SdlGlLoadTexture(preLoadSurface_,texture_)) {
			loadedToVideo_ = true;
		}
	}

} // Namespace mw.
