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

// Test to load directly to ram memory.
void testLoadTextureAtlas() {
	SDL_Surface* a = createSurface(200, 100, (char) 255, 0, 0); // Red block.
	SDL_Surface* b = createSurface(100, 200, 0, (char) 255, 0); // Green block.
	SDL_Surface* c = createSurface(200, 200, 0, 0, (char) 255); // Blue block.
	SDL_Surface* d = createSurface(30, 30, (char) 255, (char) 255, (char) 255); // White block.

	mw::TextureAtlas atlas(512, 512);

	atlas.add("tetris.bmp", 1);
	atlas.add("cross.png", 1);
	atlas.add(a, 1);
	atlas.add(b, 1);
	atlas.add(c, 1);
	atlas.add(d, 1);

	TestWindow w(atlas.getTexture(), 0, 0);
	w.startLoop();

	SDL_FreeSurface(a);
	SDL_FreeSurface(b);
	SDL_FreeSurface(c);
	SDL_FreeSurface(d);

	std::cout << "\ntestLoadTextureAtlas() sucsessfully!\n";
}

// Test to load directly to graphic memory. And draw the total texture and the newly added sprite.
void testLoadTextureAtlas2() {
	SDL_Surface* a = createSurface(200, 100, (char) 255, 0, 0); // Red block.
	SDL_Surface* b = createSurface(100, 200, 0, (char) 255, 0); // Green block.
	SDL_Surface* c = createSurface(200, 200, 0, 0, (char) 255); // Blue block.
	SDL_Surface* d = createSurface(30, 30, (char) 255, (char) 255, (char) 255); // White block.
		
	mw::TextureAtlas atlas(512, 512);
	TestWindow w(atlas.getTexture(), 0, 0);
	int nbr = 0;
	std::function<void()> func = [&]() {
		++nbr;
		mw::Sprite sprite;
		switch (nbr) {
			case 1:
				sprite = atlas.add("tetris.bmp", 1);
				break;
			case 2:
				sprite = atlas.add("cross.png", 1);
				break;
			case 3:
				sprite = atlas.add(a, 1);
				break;
			case 4:
				sprite = atlas.add(b, 1);
				break;
			case 5:
				sprite = atlas.add(c, 1);
				break;
			case 6:
				sprite = atlas.add(d, 1);
				break;
			default:
			{
				sprite = atlas.add(d, 1);
				break;
			}
		}
		if (!sprite.getTexture().isValid()) {
			std::cout << "\nNumber " << nbr << " failed to be inserted!\n";
		}
		w.setCenteredSprite(sprite);
	};
	
	w.setSpaceFunction(func);
	w.startLoop();

	SDL_FreeSurface(a);
	SDL_FreeSurface(b);
	SDL_FreeSurface(c);
	SDL_FreeSurface(d);

	std::cout << "\ntestLoadTextureAtlas2() sucsessfully!\n";
}

int main(int argc, char** argv) {
	testLoadTextureAtlas();
	testLoadTextureAtlas2();
	
	{
		mw::Sprite sprite("tetris.bmp");
		TestWindow w(sprite, 50, 50);
		w.startLoop();
	}
	
	mw::Sound sound("test.wav");
	sound.setVolume(0.5f);
	sound.play();	

	return 0;
}
