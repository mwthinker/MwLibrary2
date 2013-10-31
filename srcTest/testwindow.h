#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <mw/window.h>
#include <memory>

class TestWindow : public mw::Window {
public:
	TestWindow();

	void eventUpdate(const SDL_Event& windowEvent) override;

	bool focus_;
};

#endif // TESTWINDOW_H
