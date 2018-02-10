#include "window.h"
#include "exception.h"
#include "sprite.h"

#include <SDL_image.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace mw {

	int Window::nbrCurrentInstance = 0;

	int Window::majorVersionGl = 2;
	int Window::minorVersionGl = 1;

	Window::Window() : window_(nullptr), x_(-1), y_(-1), icon_(nullptr), width_(800), height_(800),
		title_(""), resizable_(true), bordered_(true), fullScreen_(false), sleepingTime_(-1),
		glBitfield_(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT) {
	}

	void Window::setupOpenGlContext() {
		glContext_ = SDL_GL_CreateContext(window_);
		if (SDL_GL_CreateContext == 0) {
			std::stringstream stream;
			stream << "SDL_GL_CreateContext failed: " << SDL_GetError();
			throw std::runtime_error(stream.str());
		}

		if (SDL_GL_SetSwapInterval(1) < 0) {
			std::cerr << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
		}

		if (char* version = (char*) glGetString(GL_VERSION)) {
			std::cerr << "GL_VERSION: " << version << std::endl;
			std::cerr << "GL_SHADING_LANGUAGE_VERSION: " << (char*) glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		} else {
			throw std::runtime_error("Error: unknown OpenGL version loadad!");
		}

		GLenum error = glewInit();
		if (GLEW_OK != error) {
			// Problem: glewInit failed, something is seriously wrong.
			std::stringstream stream;
			stream << "Error: " << glewGetErrorString(error);
			throw std::runtime_error(stream.str());
		}

		glGetError(); // Ignore, silly error which glew may cause.
	}

	Window::~Window() {
		if (icon_) {
			SDL_FreeSurface(icon_);
			icon_ = nullptr;
		}

		if (window_ != nullptr) {
			// A passive way to signal the textures that the current
			// OpenGL context is not active.
			++nbrCurrentInstance;

			// Clean up current OpenGL context and the window.
			SDL_GL_DeleteContext(glContext_);
			SDL_GL_UnloadLibrary();
			SDL_DestroyWindow(window_);
		}
	}

	void Window::startLoop() {
		if (!window_) {
			Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
			if (resizable_) {
				flags |= SDL_WINDOW_RESIZABLE;
			}

			if (!bordered_) {
				flags |= SDL_WINDOW_BORDERLESS;
			}

			if (x_ < 0) {
				x_ = SDL_WINDOWPOS_UNDEFINED;
			}
			if (y_ < 0) {
				y_ = SDL_WINDOWPOS_UNDEFINED;
			}

			initOpenGl();

			window_ = SDL_CreateWindow(
				title_.c_str(),
				x_,	y_,
				width_,	height_,
				flags
			);

			if (window_ == 0) {
				std::stringstream stream;
				stream << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
				throw std::runtime_error(stream.str());
			}

			if (icon_) {
				SDL_SetWindowIcon(window_, icon_);
				SDL_FreeSurface(icon_);
				icon_ = nullptr;
			}

			quit_ = false;

			setupOpenGlContext();
			++nbrCurrentInstance;

			initPreLoop();
			
			auto time = std::chrono::high_resolution_clock::now();
			while (!quit_) {
				glClear(glBitfield_);
				
				SDL_Event eventSDL;
				while (SDL_PollEvent(&eventSDL)) {
					eventUpdate(eventSDL);
				}

				auto currentTime = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> delta = currentTime - time;
				time = currentTime;
				update(delta.count());

				if (sleepingTime_ >= 0) {
					SDL_Delay(sleepingTime_);
				}
				SDL_GL_SwapWindow(window_);
			}
		}
	}

	void Window::setBordered(bool bordered) {
		if (window_) {
			SDL_SetWindowBordered(window_, bordered ? SDL_TRUE : SDL_FALSE);
		} else {
			bordered_ = bordered;
		}
	}

	void Window::setPosition(int x, int y) {
		if (window_) {
			SDL_SetWindowPosition(window_, x, y);
		} else {
			x_ = x;
			y_ = y;
		}
	}

	void Window::setResizeable(bool resizable) {
		if (window_) {
			#if SDL_VERSION_ATLEAST(2,0,5)
			SDL_SetWindowResizable(window_, resizable ? SDL_TRUE : SDL_FALSE);
			#endif
		} else {
			resizable_ = resizable;
		}
	}

	void Window::setIcon(std::string icon) {
		if (icon_) {
			SDL_FreeSurface(icon_);
			icon_ = nullptr;
		}
		icon_ = IMG_Load(icon.c_str());
		if (window_) {
			if (icon_) {
				SDL_SetWindowIcon(window_, icon_);
				SDL_FreeSurface(icon_);
				icon_ = nullptr;
			}
		}
	}

	void Window::setTitle(std::string title) {
		if (window_) {
			SDL_SetWindowTitle(window_, title.c_str());
		} else {
			title_ = title;
		}
	}

	// Return true if the program is in full screen mode.
	bool Window::isFullScreen() const {
		if (window_) {
			return (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN_DESKTOP) > 0;
		} else {
			return fullScreen_;
		}
	}

	void Window::getSize(int& width, int& height) const {
		if (window_) {
			SDL_GetWindowSize(window_, &width, &height);
		} else {
			width = width_;
			height = height_;
		}
	}

	void Window::setWindowSize(int width, int height) {
		if (window_) {
			SDL_SetWindowSize(window_, width, height);
		} else {
			width_ = width;
			height_ = height;
		}
	}

	// Return the current windows width in pixels.
	int Window::getWidth() const {
		int w, h;
		getSize(w, h);
		return w;
	}

	// Return the current windows height in pixels.
	int Window::getHeight() const {
		int w, h;
		getSize(w, h);
		return h;
	}

	void Window::setGlClear(GLbitfield glBitfield) {
		glBitfield_ = glBitfield;
	}

	void Window::setLoopSleepingTime(int sleepingTime) {
		sleepingTime_ = sleepingTime;
	}

	void Window::setFullScreen(bool fullScreen) {
		if (window_) {
			if (fullScreen != isFullScreen()) {
				if (isFullScreen()) {
					SDL_SetWindowFullscreen(window_, 0);
					SDL_SetWindowSize(window_, width_, height_);
					if (!bordered_) {
						SDL_SetWindowBordered(window_, SDL_bool::SDL_FALSE);
					}
				} else {
					SDL_GetWindowSize(window_, &width_, &height_);
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}
		} else {
			fullScreen_ = fullScreen;
		}
	}

	void Window::setOpenGlVersion(int majorVersion, int minorVersion) {
		if (!window_) {
			// Can only change opengl version before window creation.
			majorVersionGl = majorVersion;
			minorVersionGl = minorVersion;
		}
	}

	void Window::initOpenGl() {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersionGl);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersionGl);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		if (SDL_GL_LoadLibrary(0) != 0) {
			std::stringstream stream;
			stream << "SDL_GL_LoadLibrary failed: " << SDL_GetError() << std::endl;
			stream << "Failed to OpenGL version" << majorVersionGl << "." << minorVersionGl << std::endl;
			throw std::runtime_error(stream.str());
		}
	}

} // Namespace mw.
