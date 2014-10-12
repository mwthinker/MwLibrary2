#include "window.h"
#include "exception.h"
#include "sprite.h"

#if MW_OPENGLES2
#include "shader.h"
#include "matrix.h"
#endif // MW_OPENGLES2

#include <SDL_image.h>

namespace mw {

	int Window::nbrOfInstances = 0;

	void Window::initOpenGl() {
		if (nbrOfInstances < 1) {
			SDL_GL_SetSwapInterval(1);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#ifdef MW_OPENGLES2
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			if (SDL_GL_LoadLibrary(0) != 0) {
				std::printf("\n Failed to load OpenGl ES 2\n");
				std::exit(1);
			}
#endif
		}
	}

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

		initOpenGl();

		if (x < 0) {
			x = SDL_WINDOWPOS_UNDEFINED;
		}
		if (y < 0) {
			y = SDL_WINDOWPOS_UNDEFINED;
		}

		window_ = SDL_CreateWindow(
			title.c_str(),
			x,
			y,
			width,
			height,
			flags);

		if (window_ == 0) {
			throw Exception(SDL_GetError());
		}

		SDL_Surface* surface = IMG_Load(icon.c_str());
		SDL_SetWindowIcon(window_, surface);
		SDL_FreeSurface(surface);

		quit_ = false;
		time_ = 0;
		width_ = width;
		height_ = height;

		setupOpenGlContext();
		++nbrOfInstances;
	}

	void Window::setupOpenGlContext() {
		glContext_ = SDL_GL_CreateContext(window_);
#ifdef MW_OPENGLES2
		initGLES2();
		mw::Shader shader;
		shader.bindAttribute(SHADER_A_VEC4_POSITION);
		shader.bindAttribute(SHADER_A_VEC2_TEXCOORD);
		shader.loadAndLink(SHADER_VER, SHADER_FRAG);
		Shader::setDefaultShader(shader);
#endif //MW_OPENGLES2
		if (nbrOfInstances < 1) {
			std::printf("\nGL_VERSION: %s", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
			std::printf("\nGL_SHADING_LANGUAGE_VERSION: %s\n\n", reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
		}
		glClear(GL_COLOR_BUFFER_BIT);
		checkGlError();
	}

	Window::~Window() {
		if (window_ != nullptr) {
			// Clean up the shader.
			Shader::setDefaultShader(mw::Shader());
			
			// Clean up Gl context and the window.
			SDL_GL_DeleteContext(glContext_);
			SDL_DestroyWindow(window_);
		}
	}

	void Window::startLoop() {
		if (!quit_) {
			SDL_GL_MakeCurrent(window_, glContext_);
		}
		while (!quit_) {
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
