#include "texture.h"
#include "opengl.h"
#include "window.h"

#include <SDL_image.h>

#include <iostream>
#include <algorithm>
#include <tuple>
#include <cassert>

namespace mw {

	namespace helper {

		namespace {

			using Pixel1 = std::tuple<Uint8>;
			using Pixel2 = std::tuple<Uint8, Uint8>;
			using Pixel3 = std::tuple<Uint8, Uint8, Uint8>;
			using Pixel4 = std::tuple<Uint8, Uint8, Uint8, Uint8>;

			template <typename Pixel>
			void flipVerticalGeneric(SDL_Surface* surface) {
				for (int i = 0; i < surface->h / 2; ++i) {
					for (int j = 0; j < surface->w; ++j) {
						Pixel* startElement = (Pixel*) surface->pixels + i * surface->w + j;
						Pixel* endElement = (Pixel*) surface->pixels + (surface->h - i - 1) * surface->w + j;
						std::swap(*startElement, *endElement);
					}
				}
			}

		}

		void flipVertical(SDL_Surface* surface) {
			assert(surface->format->BytesPerPixel >= 1 && surface->format->BytesPerPixel <= 4);
			if (surface->format->BytesPerPixel == 4) {
				flipVerticalGeneric<Pixel4>(surface);
			} else if (surface->format->BytesPerPixel == 3) {
				flipVerticalGeneric<Pixel3>(surface);
			} else if (surface->format->BytesPerPixel == 2) {
				flipVerticalGeneric<Pixel2>(surface);
			} else if (surface->format->BytesPerPixel == 1) {
				flipVerticalGeneric<Pixel1>(surface);
			}
		}

		SDL_Surface* createSurface(int w, int h) {
			// SDL interprets each pixel as a 32-bit number, so our masks must depend
			// on the endianness (byte order) of the machine.
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			Uint32 rmask = 0xff000000;
			Uint32 gmask = 0x00ff0000;
			Uint32 bmask = 0x0000ff00;
			Uint32 amask = 0x000000ff;
#else
			Uint32 rmask = 0x000000ff;
			Uint32 gmask = 0x0000ff00;
			Uint32 bmask = 0x00ff0000;
			Uint32 amask = 0xff000000;
#endif

			return SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
		}

	}

	namespace {

		// Return an opengl texture from the surface provided. Return 0 if the
		// operation failed.
		GLuint sdlGlLoadTexture(SDL_Surface* surface) {
			GLuint textureId = 0;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			int mode = GL_RGB;
			if (surface->format->BytesPerPixel == 4) {
				mode = GL_RGBA;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
			return textureId;
		}
	}

	Texture::Texture() : 
		firstCallBind_(true),
		texture_(0),
		width_(0), height_(0),
		valid_(false),
		imageData_(std::make_shared<ImageData>([]() {})) {

	}

	Texture::Texture(std::string filename, std::function<void()> filter) : 
		firstCallBind_(true),
		texture_(0),
		width_(0), height_(0),
		valid_(false),
		imageData_(std::make_shared<ImageData>(filter)) {

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

	Texture::Texture(SDL_Surface* surface, std::function<void()> filter) : 
		firstCallBind_(true),
		texture_(0),
		width_(surface->w), height_(surface->h),
		valid_(true),
		imageData_(std::make_shared<ImageData>(surface, filter)) {

	}

	Texture::Texture(int width, int height, std::function<void()> filter) :
		firstCallBind_(true),
		texture_(0),
		width_(0), height_(0),
		valid_(false),
		imageData_(std::make_shared<ImageData>(filter)) {

		imageData_->preLoadSurface_ = helper::createSurface(width, height);
		if (imageData_->preLoadSurface_ != 0) {
			width_ = imageData_->preLoadSurface_->w;
			height_ = imageData_->preLoadSurface_->h;
			valid_ = true;
		} else {
			std::cerr << "\nEmpty image failed to be created: " << IMG_GetError() << std::endl;
			valid_ = false;
		}
	}

	bool Texture::operator==(const Texture& texture) const {
		return imageData_ == texture.imageData_;
	}

	void Texture::bindTexture() const {
		if (firstCallBind_) {
			firstCallBind_ = false;
			if (imageData_->preLoadSurface_ != nullptr) {
				imageData_->loadImageToGraphic();
				texture_ = imageData_->texture_;
				imageData_->windowInstance_ = Window::getInstanceId();
			} else {
				texture_ = imageData_->texture_;
				glBindTexture(GL_TEXTURE_2D, texture_);
				imageData_->windowInstance_ = Window::getInstanceId();
			}
		} else {
			if (texture_ != 0) {
				glBindTexture(GL_TEXTURE_2D, texture_);
			}
		}
		checkGlError();
	}
	
	Texture::ImageData::ImageData(std::function<void()> filter) :
		preLoadSurface_(0), texture_(0), filter_(filter), windowInstance_(0) {
	}

	Texture::ImageData::ImageData(SDL_Surface* surface, std::function<void()> filter) :
		preLoadSurface_(surface), texture_(0), filter_(filter), windowInstance_(0) {
	}

	void Texture::ImageData::loadImageToGraphic() const {
		// Current surface is valid?
		if (preLoadSurface_ != 0) {
			helper::flipVertical(preLoadSurface_); // SDL and opengl uses different orientations.
			texture_ = sdlGlLoadTexture(preLoadSurface_); // Load to texture.
			SDL_FreeSurface(preLoadSurface_);
			preLoadSurface_ = nullptr;

			// Texture valid?
			if (texture_ != 0) {
				filter_();
			}
		}
	}

	Texture::ImageData::~ImageData() {
		// Opengl texture? And the opengl context active?
		if (texture_ != 0 && windowInstance_ == Window::getInstanceId()) {
			// Is called if the opengl texture is valid and therefore need to be cleaned up.
			glDeleteTextures(1, &texture_);
		}

		// Safe to pass null.
		SDL_FreeSurface(preLoadSurface_);
	}

} // Namespace mw.
