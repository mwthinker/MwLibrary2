#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include "testshader.h"
#include "testshaderdata.h"
#include "drawtext.h"

#include <mw/window.h>
#include <mw/sprite.h>
#include <mw/text.h>
#include <mw/buffer.h>

#include <functional>

class TestWindow : public mw::Window {
public:
	TestWindow(mw::Sprite sprite = mw::Sprite(), int x = 0, int y = 0);

	// Execute the function when space bar is pressed.
	inline void setSpaceFunction(const std::function<void()> func) {
		func_ = func;
	}

	inline void setCenteredSprite(const mw::Sprite& sprite) {
		sprite2_ = sprite;
	}

private:
    void update(double deltaTime) override;

	void eventUpdate(const SDL_Event& windowEvent) override;

	void resize(int w, int h);

	bool focus_;
	mw::Sprite sprite_;
	mw::Sprite sprite2_;
	mw::Buffer buffer1_;
	std::shared_ptr<TestShaderData> data1_;
	std::shared_ptr<DrawText> drawText_;

	int x_, y_;
	mw::Text text_;
	std::function<void()> func_;

	std::shared_ptr<TestShader> shader_;

};

#endif // TESTWINDOW_H
