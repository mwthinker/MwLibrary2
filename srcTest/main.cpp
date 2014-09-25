#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/sound.h>

int main(int argc, char** argv) {
	// Testing starting 3 window.
	{
		mw::Sprite sprite("tetris.bmp");
		TestWindow w(sprite, 50, 50);
		w.startLoop();
	}
	{
		mw::Sprite sprite("tetris.bmp");
		TestWindow w(sprite);
		w.startLoop();
	}
	{		
		TestWindow w;
		w.startLoop();
	}
	
	mw::Sound sound("test.wav");
	sound.setVolume(0.5f);
	sound.play();	

	return 0;
}
