#ifdef MW_OPENGLES2
#include "testwindow2.h"
#else // MW_OPENGLES2
#include "testwindow.h"
#endif // MW_OPENGLES2

#include <mw/sprite.h>
#include <mw/sound.h>

#include <iostream>

int main(int argc, char** argv) {
#ifdef MW_OPENGLES2
	TestWindow2 w;
#else // MW_OPENGLES2
	// Testing starting 3 window at once.
	mw::Sprite sprite("tetris.bmp");
	TestWindow w(sprite,50,50), w2(sprite), w3;
#endif // MW_OPENGLES2
	mw::Sound sound("test.wav");
	sound.play();
	w.startLoop();

	return 0;
}
