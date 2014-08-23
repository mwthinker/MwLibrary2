#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/window.h>

TestWindow::TestWindow(mw::Sprite sprite, int x, int y) : mw::Window(-1, -1, 300, 300, true, "Test"), sprite_(sprite), x_(x), y_(y) {
	focus_ = true;
	sprite_.setDrawFunction([](const mw::Sprite& sprite) {
		const mw::Texture& texture = sprite.getTexture();
		if (texture.isValid()) {
#ifndef MW_OPENGLES2
			glColor3d(1, 1, 1);
			sprite.bind();

			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glTexCoord2f(sprite.getX() / texture.getWidth(), sprite.getY() / texture.getHeight());
			glVertex2f(0, 0);

			glTexCoord2f((sprite.getX() + sprite.getWidth()) / texture.getWidth(), sprite.getY() / texture.getHeight());
			glVertex2f(sprite.getWidth(), 0);

			glTexCoord2f((sprite.getX() + sprite.getWidth()) / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight());
			glVertex2f(sprite.getWidth(), sprite.getHeight());

			glTexCoord2f(sprite.getX() / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight());
			glVertex2f(0, sprite.getHeight());
			glEnd();
			glDisable(GL_TEXTURE_2D);
#endif
		}
	});

	mw::Font font("Ubuntu-B.ttf", 30);
	text_ = mw::Text("hej", font);
	text_.setCharacterSize(60);
	int a = 1;
}

void TestWindow::update(Uint32 msDeltaTime) {
#ifndef MW_OPENGLES2
	glPushMatrix();
	glTranslated(x_, y_, 0);
	glColor4d(1, 1, 1, 1);
	sprite_.draw();
	glColor3d(1, 0, 0);
	text_.draw();
	glPopMatrix();
#endif
}

void TestWindow::eventUpdate(const SDL_Event& windowEvent) {
	switch (windowEvent.type) {
		case SDL_QUIT:
			quit();
			break;
		case SDL_WINDOWEVENT:
			switch (windowEvent.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					if (windowEvent.window.windowID == getId()) {
						quit();
					}
					break;
				case SDL_WINDOWEVENT_RESIZED:
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					if (windowEvent.window.windowID == getId()) {
						focus_ = true;
					}
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					if (windowEvent.window.windowID == getId()) {
						focus_ = false;
					}
					break;
			}
			break;
		case SDL_KEYDOWN:
			switch (windowEvent.key.keysym.sym) {
				case SDLK_ESCAPE:
					if (focus_) {
						quit();
					}
					break;
				default:
					break;
			}
			break;
	}
}
