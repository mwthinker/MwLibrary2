#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/text.h>
#include <mw/color.h>
#include <mw/window.h>
#include <mw/matrix.h>
#include <mw/opengl.h>
#include <mw/sprite.h>

namespace {

    void draw(const TestShader& shader, const mw::Sprite& sprite) {
        const mw::Texture& texture = sprite.getTexture();
		if (texture.isValid()) {
			texture.bindTexture();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Centered square in ORIGO.
			GLfloat aPos[] = {
				-0.5f, -0.5f,
				0.5f, -0.5f,
				-0.5f, 0.5f,
				0.5f, 0.5f};

            float x = sprite.getX();
            float y = sprite.getY();
            float dx = sprite.getWidth();
            float dy = sprite.getHeight();

			// Map the sprite out from the texture.
			GLfloat aTex[] = {
				x / texture.getWidth(), y / texture.getHeight(),
				(x + dx) / texture.getWidth(), y / texture.getHeight(),
				x / texture.getWidth(), (y + dy) / texture.getHeight(),
				(x + dx) / texture.getWidth(), (y + dy) / texture.getHeight()};

			// Use the program object.
			shader.glUseProgram();
			shader.setGlTextureU(true);

			// Set the vertex pointer.
			shader.setGlPosA(2, aPos);
			shader.setGlTexA(2, aTex);

			// Upload the attributes and draw the sprite.
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glDisable(GL_BLEND);
			mw::checkGlError();
		}
	}

	void draw(const TestShader& shader, const mw::Text& text, float x = 0, float y = 0) {
		if (text.isValid()) {
			text.bindTexture();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Lower left corner is in ORIGO.
			GLfloat aPos[] = {
				x, y,
				x + text.getWidth(), y,
				x, text.getHeight() + y,
				x + text.getWidth(), text.getHeight() + y};

			// Map the sprite out from the texture.
			GLfloat aTex[] = {
				0, 0,
				1, 0,
				0, 1,
				1, 1};

			// Use the program object
			shader.glUseProgram();
			shader.setGlTextureU(true);

			// Set the vertex pointer.
			shader.setGlPosA(2, aPos);
			shader.setGlTexA(2, aTex);

			// Upload the attributes and draw the sprite.
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glDisable(GL_BLEND);
			mw::checkGlError();
		}
	}

} // Anonymous namespace.

TestWindow::TestWindow(mw::Sprite sprite, int x, int y)
	: mw::Window(2, 1, false, -1, -1, 512, 512, true, "Test"), sprite_(sprite), x_(x), y_(y),
	shader_(TEST_SHADER_VER, TEST_SHADER_FRAG) {

	focus_ = true;
	mw::Font font("Ubuntu-B.ttf", 60);
	text_ = mw::Text("hej", font);
    shader_.glUseProgram();
	glClearColor(0, 0, 0, 1);
	resize(getWidth(), getHeight());
}

void TestWindow::update(std::chrono::high_resolution_clock::duration) {
	mw::Matrix44 m = mw::getTranslateMatrix44((float) x_, (float) y_);
	mw::Matrix44 m2 = m * mw::getScaleMatrix44(sprite_.getWidth(), sprite_.getHeight())*mw::getTranslateMatrix44(0.5, 0.5);
	mw::Matrix44 m3 = m *  mw::getTranslateMatrix44(getWidth() * 0.5f, getHeight() * 0.5f) * mw::getScaleMatrix44(sprite2_.getWidth(), sprite2_.getHeight());
	// Update model matrix.
	shader_.glUseProgram();
	shader_.setGlColorU(1, 1, 1);
	shader_.setGlModelMatrixU(m2);
	draw(shader_, sprite_);
	shader_.setGlColorU(1, 1, 1);
	shader_.setGlModelMatrixU(m3);
	draw(shader_, sprite2_);
	shader_.setGlColorU(1, 0, 0);
	shader_.setGlModelMatrixU(m);
	draw(shader_, text_);
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
					resize(windowEvent.window.data1, windowEvent.window.data2);
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
				case SDLK_SPACE:
					if (func_) {
						func_();
					}
					break;
				case SDLK_ESCAPE:
					if (focus_) {
						quit();
					}
					break;
			}
			break;
	}
}

void TestWindow::resize(int w, int h) {
	glViewport(0, 0, w, h);
	shader_.setGlProjectionMatrixU(mw::getOrthoProjectionMatrix44(0, (float) w, 0, (float) h));
}
