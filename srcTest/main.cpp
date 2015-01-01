#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/sound.h>
#include <mw/textureatlas.h>

#include <iostream>
#include <cassert>

SDL_Surface* createSurface(int w, int h, char r, char g, char b) {
	SDL_Surface* s = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	SDL_FillRect(s, 0, SDL_MapRGB(s->format, r, g, b));
	return s;
}

void testLoadTextureAtlas() {
	SDL_Surface* a = createSurface(200, 100, (char) 255, 0, 0); // Red block.
	SDL_Surface* b = createSurface(100, 200, 0, (char) 255, 0); // Green block.
	SDL_Surface* c = createSurface(300, 300, 0, 0, (char) 255); // Blue block.
	SDL_Surface* d = createSurface(30, 30, (char) 255, (char) 255, (char) 255); // White block.

	mw::TextureAtlas atlas(512, 512);

	atlas.add(a);
	atlas.add(b);
	atlas.add(c);
	atlas.add(d);

	TestWindow w(atlas.getTexture(), 0, 0);
	w.startLoop();

	SDL_FreeSurface(a);
	SDL_FreeSurface(b);
	SDL_FreeSurface(c);
	SDL_FreeSurface(d);

	std::cout << "\n testLoadTextureAtlas sucsessfully!\n";
}

int main(int argc, char** argv) {
	testLoadTextureAtlas();

	// Testing starting 2 window.
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
	
	mw::Sound sound("test.wav");
	sound.setVolume(0.5f);
	sound.play();	

	return 0;
}
