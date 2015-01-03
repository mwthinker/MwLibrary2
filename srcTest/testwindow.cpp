#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/color.h>
#include <mw/window.h>
#include <mw/matrix.h>
#include <mw/defaultshader.h>

TestWindow::TestWindow(mw::Sprite sprite, int x, int y)
	: mw::Window(-1, -1, 512, 512, true, "Test"), sprite_(sprite), x_(x), y_(y) {
	
	focus_ = true;
	mw::Font font("Ubuntu-B.ttf", 60);
	text_ = mw::Text("hej", font);
#if MW_OPENGLES2
	mw::glClearColor(0, 0, 0, 1);
#else // MW_OPENGLES2
	glClearColor(0, 0, 0, 1);
#endif // MW_OPENGLES2
	resize(getWidth(), getHeight());
}

void TestWindow::update(Uint32 msDeltaTime) {
	mw::Matrix44 m = mw::getTranslateMatrix44((float) x_, (float) y_);
	mw::Matrix44 m2 = m * mw::getScaleMatrix44(sprite_.getWidth(), sprite_.getHeight())*mw::getTranslateMatrix44(0.5, 0.5);
	mw::Matrix44 m3 = m *  mw::getTranslateMatrix44(getWidth() * 0.5f, getHeight() * 0.5f) * mw::getScaleMatrix44(sprite2_.getWidth(), sprite2_.getHeight());
#if MW_OPENGLES2
	// Update model matrix.
	const mw::DefaultShader& shader = mw::DefaultShader::get();
	shader.glUseProgram();
	shader.setGlColorU(1, 1, 1);
	shader.setGlModelMatrixU(m2);
	sprite_.draw();
	shader.setGlColorU(1, 1, 1);
	shader.setGlModelMatrixU(m3);
	sprite2_.draw();
	shader.setGlColorU(1, 0, 0);
	shader.setGlModelMatrixU(m);
	text_.draw();
#else // MW_OPENGLES2
	// Update model matrix.
	glLoadIdentity();
	glMultMatrixf(m2.data());
	glColor3f(1, 1, 1);
	sprite_.draw();
	glLoadIdentity();
	glMultMatrixf(m3.data());
	sprite2_.draw();
	glColor3d(1, 0, 0);
	glLoadIdentity();
	glMultMatrixf(m.data());
	text_.draw();
#endif // MW_OPENGLES2
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
#if MW_OPENGLES2
	mw::glViewport(0, 0, w, h);
	const mw::DefaultShader& shader = mw::DefaultShader::get();
	shader.glUseProgram();
	shader.setGlProjectionMatrixU(mw::getOrthoProjectionMatrix44(0, (float) w, 0, (float) h));
#else // MW_OPENGLES2
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float) w, 0, (float) h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
#endif // MW_OPENGLES2
}
