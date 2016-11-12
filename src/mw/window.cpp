#include "window.h"
#include "exception.h"
#include "sprite.h"

#include <SDL_image.h>

#include <chrono>
#include <iostream>

namespace mw {

	int Window::nbrCurrentInstance = 0;

	Window::Window(int x, int y, int width, int height, bool resizeable,
		std::string title, std::string icon, bool borderless) : Window(x, y, width, height, resizeable, title, icon, borderless, []() {

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		const int MAJOR_VERSION = 2;
		const int MINOR_VERSION = 1;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION);

		if (SDL_GL_LoadLibrary(0) != 0) {
			std::cerr << "SDL_GL_LoadLibrary failed: " << SDL_GetError() << std::endl;
			std::cerr << "Failed to OpenGL version" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
			std::exit(1);
		}
	}) {
	}

	Window::Window(int x, int y, int width, int height, bool resizeable,
		std::string title, std::string icon, bool borderless,
		std::function<void()> initGl) {

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

		initGl();

		window_ = SDL_CreateWindow(
			title.c_str(),
			x,
			y,
			width,
			height,
			flags);

		if (window_ == 0) {
			std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
			std::exit(1);
		}

		SDL_Surface* surface = IMG_Load(icon.c_str());
		SDL_SetWindowIcon(window_, surface);
		SDL_FreeSurface(surface);

		quit_ = false;
		width_ = width;
		height_ = height;

		setupOpenGlContext();
		++nbrCurrentInstance;
	}

	void Window::setupOpenGlContext() {
		glContext_ = SDL_GL_CreateContext(window_);
		if (SDL_GL_CreateContext == 0) {
			std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
			std::exit(1);
		}

		if (SDL_GL_SetSwapInterval(1) < 0) {
			std::cerr << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << std::endl;
		}
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		if (char* version = (char*) glGetString(GL_VERSION)) {
			std::cout << "GL_VERSION: " << version << std::endl;
			std::cout << "GL_SHADING_LANGUAGE_VERSION: " << (char*) glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		} else {
			std::cerr << "Error: unknown OpenGL version loadad!" << std::endl;
			std::exit(1);
		}

		GLenum error = glewInit();
		if (GLEW_OK != error) {
			// Problem: glewInit failed, something is seriously wrong.
			std::cerr << "Error: " << glewGetErrorString(error) << std::endl;
			std::exit(1);
		}

		glGetError(); // Ignore, silly error which glew may cause.
	}

	Window::~Window() {
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
		auto time = std::chrono::high_resolution_clock::now();
		while (!quit_) {
			SDL_Event eventSDL;
			while (SDL_PollEvent(&eventSDL)) {
				eventUpdate(eventSDL);
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> delta = currentTime - time;
			update(delta.count());
			time = currentTime;

			SDL_GL_SwapWindow(window_);
		}
	}

	void Window::setFullScreen(bool fullScreen) {
		if (fullScreen != isFullScreen()) {
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
	}

} // Namespace mw.
