#include "testwindow.h"

#include <mw/window.h>
#include <memory>

TestWindow::TestWindow() : mw::Window(300, 300, true, "Test") {
	focus_ = true;
}

void TestWindow::eventUpdate(const SDL_Event& windowEvent) {
	switch (windowEvent.type) {
	case SDL_QUIT:
		quit();
		break;
	case SDL_WINDOWEVENT:
		switch (windowEvent.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			if (windowEvent.window.windowID == getId()) {
				quit();
			}
			break;
		case SDL_WINDOWEVENT_RESIZED:
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			if (windowEvent.window.windowID == getId()) {
				focus_ = true;
			}
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			if (windowEvent.window.windowID == getId()) {
				focus_ = false;
			}
			break;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (windowEvent.key.keysym.sym) {
		case SDLK_ESCAPE:
			if (focus_) {
				quit();
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
