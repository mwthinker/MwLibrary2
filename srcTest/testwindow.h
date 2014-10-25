#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <mw/window.h>
#include <mw/sprite.h>
#include <mw/text.h>
#include <mw/matrix.h>
#include <mw/shader.h>

class TestWindow : public mw::Window {
public:
	TestWindow(mw::Sprite sprite = mw::Sprite(), int x = 0, int y = 0);

	void update(Uint32 msDeltaTime) override;

	void eventUpdate(const SDL_Event& windowEvent) override;

private:
	void resize(int w, int h);

	bool focus_;
	mw::Sprite sprite_;
	int x_, y_;
	mw::Text text_;
#if MW_OPENGLES2
	mw::Shader shader_;
#endif // MW_OPENGLES2
};

#endif // TESTWINDOW_H
