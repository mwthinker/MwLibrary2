#include "window.h"
#include "exception.h"

#include <SDL_image.h>
#include <SDL_opengl.h>

namespace mw {

	std::list<Window*> Window::windows;
	std::list<Window*> Window::addWindows;

	Window::Window(int width, int height, bool resizeable, std::string title, std::string icon) {
		// Create an application window with the following settings:
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
		if (resizeable) {
			flags |= SDL_WINDOW_RESIZABLE;
		}

		window_ = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			flags);

		if (window_ == 0) {
			throw Exception(SDL_GetError());
		}

		SDL_Surface* surface = IMG_Load(icon.c_str());
		SDL_SetWindowIcon(window_, surface);
		SDL_FreeSurface(surface);

		SDL_GL_SetSwapInterval(1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		mainGLContext_ = SDL_GL_CreateContext(window_);

		quit_ = false;
		time_ = 0;
		width_ = width;
		height_ = height;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, width_, height_);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(0, width_, 0, height_, -1, 1);

		if (windows.empty()) {
			windows.push_back(this);
		} else {
			addWindows.push_back(this);
		}
	}

	Window::~Window() {
		if (window_ != nullptr) {
			SDL_GL_DeleteContext(mainGLContext_);
			SDL_DestroyWindow(window_);
			windows.remove_if([this](Window* w) {
				return getId() == w->getId();
			});
		}

		addWindows.remove_if([this](Window* w) {
			return getId() == w->getId();
		});
	}

	void Window::startLoop() {
		while (!windows.empty()) {
			SDL_Event eventSDL;
			while (SDL_PollEvent(&eventSDL)) {
				for (Window* window : windows) {
					window->eventUpdate(eventSDL);
				}
			}

			for (Window* window : windows) {
				window->updateLoop();
			}

			windows.remove_if([](Window* w) {
				if (w->quit_) {
					SDL_GL_DeleteContext(w->mainGLContext_);
					SDL_DestroyWindow(w->window_);
					w->window_ = nullptr;
				}

				return w->quit_;
			});

			addWindows.remove_if([](Window* w) {
				windows.push_back(w);
				return true;
			});
		}
	}

	void Window::updateLoop() {
		SDL_GL_MakeCurrent(window_, mainGLContext_);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Uint32 currentTime = SDL_GetTicks();
		Uint32 deltaTime = currentTime - time_;
		time_ = currentTime;

		update(deltaTime);

		SDL_GL_SwapWindow(window_);
	}

	SDL_Window* Window::getSdlWindow() const {
		return window_;
	}

	void Window::setFullScreen(bool fullScreen) {
		if (isFullScreen()) {
			SDL_SetWindowFullscreen(window_, 0);
			SDL_SetWindowSize(window_, width_, height_);
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
