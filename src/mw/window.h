#ifndef MW_WINDOW_H
#define MW_WINDOW_H

#include "initsdl.h"

#include <SDL.h>

#include <string>
#include <chrono>

namespace mw {

	// Create a window which handle all user input. The graphic is rendered using OpenGL.
	// The OpenGL view port is the whole window size and the model view is the same size as
	// the window and origo is on the left down side.
	class Window : public InitSdl {
	public:
		// Creates a window with size determined by width and height in pixels.
		Window(const int majorGlVersion, const int minorGlVersion, const bool glProfileEs,
			int x, int y, int width, int height, bool resizeable,
			std::string title = "", std::string icon = "", bool borderless = false);

		virtual ~Window();

		// Start the loop which handle all inputs and graphics in the windows. It will not
		// return until the loop is ended. Is closed when the windows is closed, i.e. a
		// call to the function quit().
		void startLoop();

		// Set the program to full screen mode or desktop mode.
		// If mode is not changed from the current mode nothing happen.
		void setFullScreen(bool fullScreen);

		// Return true if the program is in full screen mode.
		inline bool isFullScreen() const {
		    return (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN_DESKTOP) > 0;
		}

		inline void getSize(int& width, int& height) const {
		    SDL_GetWindowSize(window_, &width, &height);
		}

		// Return the current windows width in pixels.
		inline int getWidth() const {
            int w, h;
            getSize(w, h);
            return w;
		}

		// Return the current windows height in pixels.
		inline int getHeight() const {
            int w, h;
            getSize(w, h);
            return h;
		}

		// Make the program to quit as soon as the current frame is finished.
		// I.e. the loop in startLoop() will be made to stop and startLoop() will return.
		inline void quit() {
		    quit_ = true;
		}

		// The id for the windows. Is the same as calling SDL_GetWindowID.
		inline Uint32 getId() const {
		    return SDL_GetWindowID(window_);
		}

		// Return the window pointer. Use with care.
		inline SDL_Window* getSdlWindow() const {
		    return window_;
		}

		// Return the number, first instance of an active window return 1 next 3, etc.
		// Each even number represent that the last widow with the odd number was closed.
		inline static int getInstanceId() {
			return nbrCurrentInstance;
		}

	private:
		// Is called by the loop. The frequency in which this function is called is fixed
		// by the vertical frequency of the monitor (VSYNC).
		inline virtual void update(std::chrono::high_resolution_clock::duration) {
		}

		// Is called by the loop. Is called when ever a SDL_EVENT occurs.
		inline virtual void eventUpdate(const SDL_Event& windowEvent) {
		}

		void setupOpenGlContext();

		SDL_Window* window_;
		SDL_GLContext glContext_;
		int width_, height_;
		bool quit_;
		bool borderless_;

		static int nbrCurrentInstance;
	};

} // Namespace mw.

#endif // MW_WINDOW_H

