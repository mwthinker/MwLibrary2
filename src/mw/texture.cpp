#include "texture.h"

#include <SDL_image.h>
#include <SDL_opengl.h>

#include <iostream>

namespace mw {

	namespace {

		// Returns an opengl texture from the surface provided. Return 0 if the
		// operation failed.
		GLuint sdlGlLoadTexture(SDL_Surface* const surface) {
			GLuint textureId = 0;
			glGenTextures(1, &textureId);
			int mode = GL_RGB;
			if (surface->format->BytesPerPixel == 4) {
				mode = GL_RGBA;
			}

			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
			return textureId;
		}

	}

	Texture::Texture(std::string filename, std::function<void()> filter) : preLoadSurface_(0), firstCallToBind_(true), texture_(0), filter_(filter) {
		preLoadSurface_ = IMG_Load(filename.c_str());
		if (preLoadSurface_ == 0) {
			std::cerr << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;
		}
	}

	Texture::Texture(SDL_Surface* surface, std::function<void()> filter) : preLoadSurface_(surface), firstCallToBind_(true), texture_(0), filter_(filter) {
	}

	Texture::~Texture() {
		if (texture_ != 0) {
			// Is called if the opengl texture is valid and therefore need to be cleaned up.
			glDeleteTextures(1, &texture_);
		}

		// Safe to pass null.
		SDL_FreeSurface(preLoadSurface_);
	}

	void Texture::bind() const {
		if (firstCallToBind_) {
			firstCallToBind_ = false;

			// Current surface is valid?
			if (preLoadSurface_ != 0) {
				// Load to texture.
				texture_ = sdlGlLoadTexture(preLoadSurface_);
				SDL_FreeSurface(preLoadSurface_);
				preLoadSurface_ = nullptr;

				// Texture valid?
				if (texture_ != 0) {
					filter_();
				}
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

} // Namespace mw.
