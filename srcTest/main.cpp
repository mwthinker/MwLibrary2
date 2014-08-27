#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/sound.h>

#include <iostream>

int main(int argc, char** argv) {
	// Testing starting 3 window at once.
	mw::Sprite sprite("tetris.bmp");
	TestWindow w(sprite,50,50), w2(sprite), w3;

	mw::Sound sound("test.wav");
	sound.play();
	w.startLoop();

	return 0;
}
