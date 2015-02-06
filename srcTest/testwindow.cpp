#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/text.h>
#include <mw/color.h>
#include <mw/window.h>
#include <mw/matrix.h>

namespace {

#if MW_OPENGLES2
    void draw(const TestShader& shader, const mw::Sprite& sprite) {
        const mw::Texture& texture = sprite.getTexture();
		if (texture.isValid()) {
			texture.bindTexture();
			mw::glEnable(GL_BLEND);
			mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			mw::glDisable(GL_BLEND);
			mw::checkGlError();
		}
	}
#else // MW_OPENGLES2
    void draw(const mw::Sprite& sprite) {
        const mw::Texture& texture = sprite.getTexture();
		if (texture.isValid()) {
			texture.bindTexture();
			float x = sprite.getX();
            float y = sprite.getY();
            float dx = sprite.getWidth();
            float dy = sprite.getHeight();
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			glTexCoord2f(x/ texture.getWidth(), y / texture.getHeight());
			glVertex2f(-0.5, -0.5);

			glTexCoord2f((x + dx) / texture.getWidth(), y / texture.getHeight());
			glVertex2f(0.5, -0.5);

			glTexCoord2f((x + dx) / texture.getWidth(), (y + dy) / texture.getHeight());
			glVertex2f(0.5, 0.5);

			glTexCoord2f(x / texture.getWidth(), (y + dy) / texture.getHeight());
			glVertex2f(-0.5, 0.5);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);

			mw::checkGlError();
		}
	}
#endif // MW_OPENGLES2

#if MW_OPENGLES2
void draw(const TestShader& shader, const mw::Text& text, float x = 0, float y = 0) {
		const mw::Texture& texture = text.getTexture();
		if (texture.isValid()) {
			texture.bindTexture();
			mw::glEnable(GL_BLEND);
			mw::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Lower left corner is in ORIGO.
			GLfloat aPos[] = {
				x, y,
				x + texture.getWidth(), y,
				x, texture.getHeight() + y,
				x + texture.getWidth(), texture.getHeight() + y};

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
			mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			mw::glDisable(GL_BLEND);
			mw::checkGlError();
		}
	}
#else // MW_OPENGLES2
    void draw(const mw::Text& text, float x = 0, float y = 0) {
		const mw::Texture& texture = text.getTexture();
		if (texture.isValid()) {
			texture.bindTexture();
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(x, y);

			glTexCoord2f(1, 0);
			glVertex2f(x + texture.getWidth(), y);

			glTexCoord2f(1, 1);
			glVertex2f(x + texture.getWidth(), y + texture.getHeight());

			glTexCoord2f(0, 1);
			glVertex2f(x, y + texture.getHeight());
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			mw::checkGlError();
		}
	}
#endif // MW_OPENGLES2

} // Anonymous namespace.

TestWindow::TestWindow(mw::Sprite sprite, int x, int y)
	: mw::Window(-1, -1, 512, 512, true, "Test"), sprite_(sprite), x_(x), y_(y)
	#if MW_OPENGLES2
	,shader_(TEST_SHADER_VER, TEST_SHADER_FRAG)
	#endif // MW_OPENGLES2
	{

	focus_ = true;
	mw::Font font("Ubuntu-B.ttf", 60);
	text_ = mw::Text("hej", font);
#if MW_OPENGLES2
    shader_.glUseProgram();
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
#else // MW_OPENGLES2
	// Update model matrix.
	glLoadIdentity();
	glMultMatrixf(m2.data());
	glColor3f(1, 1, 1);
	draw(sprite_);
	glLoadIdentity();
	glMultMatrixf(m3.data());
	draw(sprite2_);
	glColor3d(1, 0, 0);
	glLoadIdentity();
	glMultMatrixf(m.data());
	draw(text_);
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
	shader_.setGlProjectionMatrixU(mw::getOrthoProjectionMatrix44(0, (float) w, 0, (float) h));
#else // MW_OPENGLES2
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float) w, 0, (float) h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
#endif // MW_OPENGLES2
}
