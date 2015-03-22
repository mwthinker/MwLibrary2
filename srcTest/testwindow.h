#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include "testshader.h"

#include <mw/window.h>
#include <mw/sprite.h>
#include <mw/text.h>

#include <functional>

class TestWindow : public mw::Window {
public:
	TestWindow(mw::Sprite sprite = mw::Sprite(), int x = 0, int y = 0);

	void update(Uint32 msDeltaTime) override;

	void eventUpdate(const SDL_Event& windowEvent) override;

	// Execute the function when space bar is pressed.
	inline void setSpaceFunction(const std::function<void()> func) {
		func_ = func;
	}

	inline void setCenteredSprite(const mw::Sprite& sprite) {
		sprite2_ = sprite;
	}

private:
	void resize(int w, int h);

	bool focus_;
	mw::Sprite sprite_;
	mw::Sprite sprite2_;

	int x_, y_;
	mw::Text text_;
	std::function<void()> func_;

	TestShader shader_;

};

#endif // TESTWINDOW_H
