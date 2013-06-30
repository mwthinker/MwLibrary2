#ifndef MW_WINDOW_H
#define MW_WINDOW_H

#include "initsdl.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <string>
#include <vector>

namespace mw {

	// Creates a window and handles input, etc. The graphic is rendered using opengl.
	// The opengl viewport is whole window size and the modelview is the same size as 
	// the window and origo is on the left down side.
	// May only use one instance of Window at a time else (undetermined behavior).
	class Window : public InitSdl {
	public:
		// Creates a window with size determined by width and height in pixels.
		Window(int width, int height, bool resizeable, std::string title="", std::string icon="");

		virtual ~Window();

		// Starts a loop which handles all events and graphics in the window. It will not return until the loop is ended.
		// Is closed when the windows is closed, i.e. a call to the protected function setQuiting(true).
		void startLoop();

	protected:
		// Gets the window pointer.
		SDL_Window* getSdlWindow() const;

		// Sets the program in fullscreeen mode if true else in windows mode.
		// If mode is not changed from current mode, isFullScreen(), nothing happens.
		void setFullScreen(bool fullScreen);
		
		// Returns true if the program is in fullscreen mode.
		bool isFullScreen() const;

		// Returns the current windows width in pixels.
		int getWidth() const;
		
		// Returns the current windows height in pixels.
		int getHeight() const;

		// Makes the program to quit as soon as current frame is finnished.
		// i.e. the loop in startLoop() will be made to stop and startloop() will return.
		void quit();

	private:
		// Is called by the loop. The frequency in which this function is called is fixed
		// by the vertical frequency of the monitor (VSYNC). The time between two calls can vary,
		// but is displayed in parameter msDeltaTime in milliseconds.
		// Is intenden to be inherited, and is in this implemention empty.
		virtual void update(Uint32 msDeltaTime);

		// Is called by the loop. Is called when ever a SDL_EVENT occure, and the event is in windowEvent.
		// Is intenden to be inherited, but has a simple implemention which handles
		// the closing of the window.
		// The resize event will not be showed in here, it is handled by resize fucntion.
		virtual void eventUpdate(const SDL_Event& windowEvent);

		// Is called once before the gameloops stops.
		virtual void onQuiting() const;

		bool quit_;

		int width_, height_;
		unsigned int time_;
		
		SDL_Window* window_;
		SDL_GLContext mainGLContext_;
	};

} // Namespace mw.

#endif // MW_WINDOW_H
