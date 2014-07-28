#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/sound.h>

#include <iostream>

mw::Sprite sprite("tetris.bmp");

int main(int argc, char** argv) {
	// Testing starting 3 window at once.
	mw::Sound sound("test.wav");
	sound.play();

	TestWindow game(sprite,50,50), game2(sprite), game3;
	game.startLoop();

	return 0;
}
