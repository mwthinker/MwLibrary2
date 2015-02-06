#include "window.h"
#include "exception.h"
#include "sprite.h"

#if MW_OPENGLES2
#include "matrix.h"
#endif // MW_OPENGLES2

#include <SDL_image.h>

#include <iostream>

namespace mw {

	int Window::nbrCurrentInstance = 0;

	Window::Window(int x, int y, int width, int height, bool resizeable, std::string title, std::string icon, bool borderless) {
		// Create an application window with the following settings:
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
		if (resizeable) {
			flags |= SDL_WINDOW_RESIZABLE;
		}
		borderless_ = borderless;
		if (borderless) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (x < 0) {
			x = SDL_WINDOWPOS_UNDEFINED;
		}
		if (y < 0) {
			y = SDL_WINDOWPOS_UNDEFINED;
		}

#ifdef MW_OPENGLES2
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		if (SDL_GL_LoadLibrary(0) != 0) {
			std::cout << "\nSDL_GL_LoadLibrary failed: " << SDL_GetError() << "\nFailed to load OpenGl ES 2" << std::endl;
			std::exit(1);
		}
#endif // MW_OPENGLES2
		
		window_ = SDL_CreateWindow(
			title.c_str(),
			x,
			y,
			width,
			height,
			flags);

		if (window_ == 0) {
			std::cout << "\nSDL_CreateWindow failed: " << SDL_GetError() << std::endl;
			std::exit(1);
		}

		SDL_Surface* surface = IMG_Load(icon.c_str());
		SDL_SetWindowIcon(window_, surface);
		SDL_FreeSurface(surface);

		quit_ = false;
		time_ = 0;
		width_ = width;
		height_ = height;

		setupOpenGlContext();
		++nbrCurrentInstance;
	}

	void Window::setupOpenGlContext() {
		glContext_ = SDL_GL_CreateContext(window_);
		if (SDL_GL_SetSwapInterval(1) < 0) {
			std::cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
		}
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifdef MW_OPENGLES2
		initGLES2();
#endif // MW_OPENGLES2
		std::cout << "\nGL_VERSION: " << reinterpret_cast<const char *>(glGetString(GL_VERSION)) << std::endl;
		std::cout << "GL_SHADING_LANGUAGE_VERSION: " << reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
		glClear(GL_COLOR_BUFFER_BIT);
		checkGlError();
	}

	Window::~Window() {
		if (window_ != nullptr) {
			// In order to signal the the current gl context is not active.
			++nbrCurrentInstance;

			// Clean up Gl context and the window.
			SDL_GL_DeleteContext(glContext_);
#ifdef MW_OPENGLES2
			SDL_GL_UnloadLibrary();
#endif // MW_OPENGLES2
			SDL_DestroyWindow(window_);
		}
	}

	void Window::startLoop(Uint32 delta) {
		while (!quit_) {
			SDL_Event eventSDL;
			while (SDL_PollEvent(&eventSDL)) {
				eventUpdate(eventSDL);
			}

			Uint32 currentTime = SDL_GetTicks();
			Uint32 deltaTime = currentTime - time_;
			if (deltaTime >= delta) {
				// Only update the screen at chosen interval.
				// Solve the problem where the SDL_GetTicks is imprecise
				// under some delta on some platforms.
				time_ = currentTime;
				update(deltaTime);
			}

			SDL_GL_SwapWindow(window_);
		}
	}

	SDL_Window* Window::getSdlWindow() const {
		return window_;
	}

	void Window::setFullScreen(bool fullScreen) {
		if (isFullScreen()) {
			SDL_SetWindowFullscreen(window_, 0);
			SDL_SetWindowSize(window_, width_, height_);
			if (borderless_) {
				SDL_SetWindowBordered(window_, SDL_bool::SDL_FALSE);
			}
		} else {
			SDL_GetWindowSize(window_, &width_, &height_);
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
	}

	bool Window::isFullScreen() const {
		return (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN_DESKTOP) > 0;
	}

	int Window::getWidth() const {
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return w;
	}

	int Window::getHeight() const {
		int w, h;
		SDL_GetWindowSize(window_, &w, &h);
		return h;
	}

	void Window::getSize(int& width, int& height) {
		SDL_GetWindowSize(window_, &width, &height);
	}

	void Window::quit() {
		quit_ = true;
	}

	Uint32  Window::getId() const {
		return SDL_GetWindowID(window_);
	}

	void Window::update(Uint32 deltaTime) {
	}

	void Window::eventUpdate(const SDL_Event& windowEvent) {
	}

} // Namespace mw.
