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

	Texture::Texture() : imageData_(std::make_shared<ImageData>([](){})), width_(0), height_(0), valid_(false) {
	}

	Texture::Texture(std::string filename, std::function<void()> filter) : imageData_(std::make_shared<ImageData>(filter)), width_(0), height_(0) {
		imageData_->preLoadSurface_ = IMG_Load(filename.c_str());
		if (imageData_->preLoadSurface_ != 0) {
			width_ = imageData_->preLoadSurface_->w;
			height_ = imageData_->preLoadSurface_->h;
			valid_ = true;
		} else {
			std::cerr << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;
			valid_ = false;
		}
	}

	Texture::Texture(SDL_Surface* surface, std::function<void()> filter) : imageData_(std::make_shared<ImageData>(surface, filter)), width_(surface->w), height_(surface->h), valid_(true) {
	}

	void Texture::bind() const {
		imageData_->bind();
	}

	int Texture::getWidth() const {
		return width_;
	}

	int Texture::getHeight() const {
		return height_;
	}

	bool Texture::isValid() const {
		return valid_;
	}

	void Texture::ImageData::bind() const {
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

	Texture::ImageData::~ImageData() {
		if (texture_ != 0) {
			// Is called if the opengl texture is valid and therefore need to be cleaned up.
			glDeleteTextures(1, &texture_);
		}

		// Safe to pass null.
		SDL_FreeSurface(preLoadSurface_);
	}

} // Namespace mw.
