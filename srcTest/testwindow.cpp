#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/text.h>
#include <mw/color.h>
#include <mw/window.h>
#include <mw/matrix44.h>
#include <mw/opengl.h>
#include <mw/sprite.h>

#include <iostream>

TestWindow::TestWindow(mw::Sprite sprite) : sprite_(sprite), buffer1_(mw::Buffer::STATIC) {
	mw::Window::setWindowSize(512, 512);
	mw::Window::setTitle("Test");
	mw::Window::setIcon("tetris.bmp");
}

void TestWindow::update(double deltaTime) {	
	Mat44 m = mw::getScaleMatrix44<float>(sprite_.getWidth(), sprite_.getHeight())*mw::getTranslateMatrix44<float>(0.5, 0.5);
	Mat44 m2 = m *  mw::getTranslateMatrix44<float>(getWidth() * 0.5f, getHeight() * 0.5f) * mw::getScaleMatrix44<float>(sprite2_.getWidth(), sprite2_.getHeight());
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Update model matrix.
	shader_->useProgram();
	shader_->setColorU(1, 1, 1);
	shader_->setModelMatrixU(m);
	shader_->setTextureU(true);
	sprite_.bindTexture();
	data1_->drawTRIANGLES();
	shader_->setColorU(1, 1, 1);
	shader_->setModelMatrixU(m2);
	data1_->drawTRIANGLES();
	shader_->setColorU(1, 0, 0);
	shader_->setModelMatrixU(m);
	
	drawText_->draw();
	
	glDisable(GL_BLEND);
	mw::checkGlError();
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
		case SDL_MOUSEBUTTONDOWN:
			if (windowEvent.button.button == SDL_BUTTON_LEFT) {
				if (windowEvent.button.clicks == 2) {
					setFullScreen(!isFullScreen());
				}
			}
			break;
	}
}

void TestWindow::resize(int w, int h) {
	glViewport(0, 0, w, h);
	shader_->setProjectionMatrixU(mw::getOrthoProjectionMatrix44<GLfloat>(0, (GLfloat) w, 0, (GLfloat) h));
}

void TestWindow::initPreLoop() {
	focus_ = true;
	shader_ = std::make_shared<TestShader>("testShader2_1.ver.glsl", "testShader2_1.fra.glsl");
	mw::Font font("Ubuntu-B.ttf", 60);
	text_ = mw::Text("hej", font);
	shader_->useProgram();
	glClearColor(0, 0, 0, 1);
	resize(getWidth(), getHeight());
	data1_ = std::make_shared<TestShaderData>(shader_);
	// Testing empty data.
	data1_->begin();
	data1_->addEmptySquareTRIANGLES();
	data1_->end();
	// Use real data.
	data1_->begin();
	data1_->addSquareTRIANGLES(-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, sprite_);
	data1_->end();

	drawText_ = std::make_shared<DrawText>(shader_, text_, 0.f, 0.f);
	buffer1_.addVertexData(data1_);
	buffer1_.addVertexData(drawText_);
	buffer1_.uploadToGraphicCard();
}
