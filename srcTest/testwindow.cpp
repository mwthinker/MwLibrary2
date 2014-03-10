#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/window.h>

TestWindow::TestWindow(mw::Sprite sprite, int x, int y) : mw::Window(300, 300, true, "Test"), sprite_(sprite), x_(x), y_(y) {
	focus_ = true;
	sprite_.setDrawPixelSize(true);
	mw::Font font("Ubuntu-B.ttf", 30);
	text_ = mw::Text("hej", font);
	text_.setCharacterSize(60);
	int a = 1;
}

void TestWindow::update(Uint32 msDeltaTime) {
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glColor4d(1, 1, 1, 1);
	sprite_.draw();
	glColor3d(1, 0, 0);
	text_.draw();
	glPopMatrix();
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
