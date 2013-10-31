#ifndef MW_WINDOW_H
#define MW_WINDOW_H

#include "initsdl.h"

#include <SDL.h>

#include <string>
#include <list>

namespace mw {

	// Creates a window and handles input, etc. The graphic is rendered using opengl.
	// The opengl view port is whole window size and the model view is the same size as 
	// the window and origo is on the left down side.
	// May only use one instance of Window at a time else (undetermined behavior).
	class Window : public InitSdl {
	public:
		// Creates a window with size determined by width and height in pixels.
		Window(int width, int height, bool resizeable, std::string title = "", std::string icon = "");

		virtual ~Window();

		// Starts a loop which handles all inputs and graphics in the windows. It will not 
		// return until the loop is ended. Is closed when the windows is closed, i.e. a 
		// call to the protected function quit().
		static void startLoop();

		Uint32 getId() const;
	protected:
		// Gets the window pointer. Use with care.
		SDL_Window* getSdlWindow() const;

		// Sets the program in full screen mode if true else in windows mode.
		// If mode is not changed from current mode, isFullScreen(), nothing happens.
		void setFullScreen(bool fullScreen);

		// Returns true if the program is in full screen mode.
		bool isFullScreen() const;

		// Returns the current windows width in pixels.
		int getWidth() const;

		// Returns the current windows height in pixels.
		int getHeight() const;

		void getSize(int& width, int& height);

		// Makes the program to quit as soon as current frame is finished.
		// I.e. the loop in startLoop() will be made to stop and startloop() will return.
		void quit();

	private:
		// The internal loop code.
		void updateLoop();

		// Is called by the loop. The frequency in which this function is called is fixed
		// by the vertical frequency of the monitor (VSYNC). The time between two calls can vary,
		// but is displayed in parameter msDeltaTime in milliseconds.
		// Is intended to be inherited, and is in this implementation empty.
		virtual void update(Uint32 msDeltaTime);

		// Is called by the loop. Is called when ever a SDL_EVENT occurs, and the event is in windowEvent.
		// Is intended to be inherited, but has a simple implementation which handles
		// the closing of the window.
		virtual void eventUpdate(const SDL_Event& windowEvent);

		bool quit_;

		int width_, height_;
		unsigned int time_;

		SDL_Window* window_;
		SDL_GLContext mainGLContext_;

		static std::list<Window*> windows, addWindows;
	};

} // Namespace mw.

#endif // MW_WINDOW_H
