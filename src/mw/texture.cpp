#include "texture.h"
#include "window.h"

#include <SDL_image.h>
#include <SDL_opengl.h>

#include <iostream>

namespace mw {

	namespace {

		// Creates and returns an opengl texture from the surface provided.
		bool sdlGlLoadTexture(SDL_Surface* const surface, GLuint& textureId) {
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

	Texture::Texture(std::string filename,  std::function<void()> filter) : preLoadSurface_(0), filter_(filter), texture_(0) {
		preLoadSurface_ = IMG_Load(filename.c_str());
		if (preLoadSurface_ == 0) {
			std::cout << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;			
		}
	}

	Texture::Texture(int width, int height, int pixelSize, void* data, std::function<void()> filter) : filter_(filter), texture_(0) {
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
	}

	Texture::Texture(SDL_Surface* surface, std::function<void()> filter) : preLoadSurface_(surface), filter_(filter), texture_(0) {
	}

	SDL_Surface* Texture::getSdlSurface() const {
		return preLoadSurface_;
	}

	Texture::~Texture() {
		if (texture_ != 0) {
			// Is called if the opengl texture is valid and therefore need to be cleaned up.
			glDeleteTextures(1,&texture_);
		}

		// Safe to pass null.
		SDL_FreeSurface(preLoadSurface_);
	}

	void Texture::bind() {
		if (texture_ == 0) {
			// Current surface is valid?
			if (preLoadSurface_ != 0) {
				loadToVideo();
			}
			// Texture valid?
			if (texture_ != 0) {
				filter_();
			}
		} else {
			// Texture valid?
			if (texture_ != 0) {
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

	bool Texture::isValid() const {
		return preLoadSurface_ != 0;
	}

	void Texture::loadToVideo() {
		if (preLoadSurface_ != 0) {
			sdlGlLoadTexture(preLoadSurface_, texture_);
		}
	}

} // Namespace mw.
