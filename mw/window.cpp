#include "window.h"
#include "joystick.h"

#include <SDL_opengl.h>
#include <iostream>

namespace mw {

	int Window::videoId_ = 0;

	Window::Window(int width, int height) {
		// Create an application window with the following settings:
		window_ = SDL_CreateWindow( 
			"An SDL2 window",                  //    window title
			SDL_WINDOWPOS_UNDEFINED,           //    initial x position
			SDL_WINDOWPOS_UNDEFINED,           //    initial y position
			640,                               //    width, in pixels
			480,                               //    height, in pixels
			SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL //    flags - see below
			);

		if (window_ == 0) {
			throw Exception(SDL_GetError());
		}
		
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
	}

	Window::~Window() {
		SDL_GL_DeleteContext(mainGLContext_);
		SDL_DestroyWindow(window_);
	}

	void Window::startLoop() {
		quit_ = false;		

		while (!quit_) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			SDL_Event eventSDL;
			while (SDL_PollEvent(&eventSDL)) {
				eventUpdate(eventSDL);
			}

			Uint32 currentTime = SDL_GetTicks();
			Uint32 deltaTime = currentTime - time_;
			time_ = currentTime;

			update(deltaTime);
			
			SDL_GL_SwapWindow(window_);
		}
	}

	// Returns an integer. If the openGl context is lost, the video id will be changed (i.e. old+1).
	// Change indicates that all openGl context need to be reloaded.
	int Window::getVideoId() {
		return videoId_;
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
		int w,h;
		SDL_GetWindowSize(window_, &w, &h);
		return w;
	}

	int Window::getHeight() const {
		int w,h;
		SDL_GetWindowSize(window_, &w, &h);
		return h;
	}

	Uint32 Window::timeTick() {
		return SDL_GetTicks();
	}

	void Window::quit() {
		quit_ = true;
	}	

	void Window::update(Uint32 deltaTime) {
	}

	void Window::eventUpdate(const SDL_Event& windowEvent) {		
	}

	void Window::onQuiting() const {		
	}

} // Namespace mw.
