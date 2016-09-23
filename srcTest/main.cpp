#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/sound.h>
#include <mw/textureatlas.h>
#include <mw/matrix.h>

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

bool equal(float a, float b) {
    return std::abs(a - b) < 0.01f;
}

bool equal(const Mat44& a, const Mat44& b) {
    for (int i = 0; i < 16; ++i) {
        if (!equal(a[i], b[i])) {
            return false;
        }
    }
    return true;
}

bool equalZERO(const Mat44& m) {
	for (float element : m) {
		if (!equal(element, 0)) {
			return false;
		}
	}
	return true;
}

void print(const Mat44& m) {
    std::cout << "\nMatrix\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << m(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void testMatrix() {
	//const Mat44 a = Mat44::I<float>;
	const Mat44 b = Mat44::I;

	Mat44 m(1, 3.1f, 7.2f, 3.9f,
		9.1f, 1.3f, 2.f, 0.1f,
		0.3f, 0.9f, 11.f, 12.f,
		12.f, 0.4f, 0.5f, 5.f);

    assert(equal(m, m));
    auto m2 = Mat44::I + m;
    assert(!equal(m, m2));

	// Test constants.
	assert(equalZERO(Mat44::ZERO));
	assert(equal(Mat44::I(0,0), 1) && equal(Mat44::I(0, 1), 0) && equal(Mat44::I(0, 2), 0) && equal(Mat44::I(0, 3), 0) &&
		equal(Mat44::I(1, 0), 0) && equal(Mat44::I(1, 1), 1) && equal(Mat44::I(1, 2), 0) && equal(Mat44::I(1, 3), 0) &&
		equal(Mat44::I(2, 0), 0) && equal(Mat44::I(2, 1), 0) && equal(Mat44::I(2, 2), 1) && equal(Mat44::I(2, 3), 0) &&
		equal(Mat44::I(3, 0), 0) && equal(Mat44::I(3, 1), 0) && equal(Mat44::I(3, 2), 0) && equal(Mat44::I(3, 3), 1));

    // Test rotation!
    m2 = m;
    mw::rotate2D(m2, 0.3f);
    assert(equal(m * mw::getRotateMatrix44<float>(0.3f, 0, 0, 1), m2));

    // Test translation!
    m2 = m;
    mw::translate2D(m2, 2.f, 3.f);
    assert(equal(m * mw::getTranslateMatrix44<float>(2.f, 3.f), m2));

    // Test scaling!
    m2 = m;
    mw::scale2D(m2, 2.f, 3.f);
    assert(equal(m * mw::getScaleMatrix44<float>(2.f, 3.f, 1), m2));

    std::cout << "\ntestMatrix() sucsessfully!\n";
}

int main(int argc, char** argv) {
    testMatrix();
	testLoadTextureAtlas();
	testLoadTextureAtlas2();

	mw::Sound sound("test.wav");
	sound.setVolume(0.5f);
	sound.play();

	return 0;
}
