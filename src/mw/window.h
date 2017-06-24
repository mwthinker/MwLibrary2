#ifndef MW_WINDOW_H
#define MW_WINDOW_H

#include "initsdl.h"

#include <SDL.h>

#include <string>
#include <functional>

namespace mw {

	// Create a window which handle all user input. The graphic is rendered using OpenGL.
	// The OpenGL view port is the whole window size and the model view is the same size as
	// the window and origo is on the left down side.
	class Window : public InitSdl {
	public:
		Window();

		virtual ~Window();

		// Start the loop which handle all inputs and graphics in the windows. It will not
		// return until the loop is ended. Is closed when the windows is closed, i.e. a
		// call to the function quit().
		void startLoop();

		// Set the program to full screen mode or desktop mode.
		// If mode is not changed from the current mode nothing happen.
		void setFullScreen(bool fullScreen);

		// Return true if the program is in full screen mode.
		bool isFullScreen() const;

		void getSize(int& width, int& height) const;

		// Return the current windows width in pixels.
		int getWidth() const;

		// Return the current windows height in pixels.
		int getHeight() const;

		// Make the program to quit as soon as the current frame is finished.
		// I.e. the loop in startLoop() will be made to stop and startLoop() will return.
		void quit() {
			quit_ = true;
		}

		// The id for the windows. Is the same as calling SDL_GetWindowID.
		Uint32 getId() const {
			return SDL_GetWindowID(window_);
		}

		// Return the window pointer. Use with care.
		SDL_Window* getSdlWindow() const {
			return window_;
		}

		// Return the number, first instance of an active window return 1 next 3, etc.
		// Each even number represent that the last widow with the odd number was closed.
		inline static int getInstanceId() {
			return nbrCurrentInstance;
		}

		void setPosition(int x, int y);

		void setBordered(bool bordered);

		void setResizeable(bool resizable);

		void setIcon(std::string icon);

		void setTitle(std::string title);

		void setWindowSize(int width, int height);

		void setOpenGlVersion(int majorVersion, int minorVersion);

	protected:
		virtual void initOpenGl();

		virtual void initPreLoop() {
		}

	private:
		// Is called by the loop. The frequency in which this function is called is fixed
		// by the vertical frequency of the monitor (VSYNC).
		virtual void update(double deltaTime) {
		}

		// Is called by the loop. Is called when ever a SDL_EVENT occurs.
		virtual void eventUpdate(const SDL_Event& windowEvent) {
		}

		void setupOpenGlContext();

		SDL_Window* window_;
		SDL_GLContext glContext_;
		int width_, height_;
		bool quit_;
		bool fullScreen_;
		bool bordered_;
		bool resizable_;
		int x_, y_;
		std::string title_;
		SDL_Surface* icon_;
		int majorVersionGl_, minorVersionGl_;

		static int nbrCurrentInstance;
	};

} // Namespace mw.

#endif // MW_WINDOW_H
