#include "testwindow.h"

#include <mw/sprite.h>
#include <mw/color.h>
#include <mw/window.h>
#include <mw/matrix.h>
#include <mw/shader.h>

namespace {

	void drawFunction(mw::Sprite& sprite) {
		const mw::Texture& texture = sprite.getTexture();
		if (texture.isValid()) {
			sprite.bindTexture();

#if MW_OPENGLES2
			GLfloat aVertices[] = {
				0, 0,
				sprite.getWidth(), 0,
				0, sprite.getHeight(),
				sprite.getWidth(), sprite.getHeight()};

			GLfloat aTexCoord[] = {
				sprite.getX() / texture.getWidth(), sprite.getY() / texture.getHeight(),
				(sprite.getX() + sprite.getWidth()) / texture.getWidth(), sprite.getY() / texture.getHeight(),
				sprite.getX() / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight(),
				(sprite.getX() + sprite.getWidth()) / texture.getWidth(), (sprite.getY() + sprite.getHeight()) / texture.getHeight()};

			// Use the program object
			auto& program = mw::Shader::getDefaultShader();
			program->glUseProgram();
			mw::glUniform1f(mw::Shader::getDefaultShader()->getUniformLocation(mw::SHADER_U_FLOAT_TEXTURE), 1);

			// Load the vertex data.
			mw::glVertexAttribPointer(program->getAttributeLocation(mw::SHADER_A_VEC4_POSITION), 2, GL_FLOAT, GL_FALSE, 0, aVertices);
			mw::glVertexAttribPointer(program->getAttributeLocation(mw::SHADER_A_VEC2_TEXCOORD), 2, GL_FLOAT, GL_FALSE, 0, aTexCoord);
			mw::glEnableVertexAttribArray(program->getAttributeLocation(mw::SHADER_A_VEC4_POSITION));
			mw::glEnableVertexAttribArray(program->getAttributeLocation(mw::SHADER_A_VEC2_TEXCOORD));

			// Upload the attributes and draw the sprite.
			mw::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else // MW_OPENGLES2
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
#endif // MW_OPENGLES2
		}
	}

}

TestWindow::TestWindow(mw::Sprite sprite, int x, int y) : mw::Window(-1, -1, 300, 300, true, "Test"), sprite_(sprite), x_(x), y_(y) {
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
#if MW_OPENGLES2
	// Update model matrix.
	auto shader = mw::Shader::getDefaultShader();
	shader->glUseProgram();
	mw::Matrix44 m = mw::getTranslateMatrix44((float) x_, (float) y_);
	mw::glUniformMatrix4fv(shader->getUniformLocation(mw::SHADER_U_MAT4_MODEL), 1, false, m.data());
	mw::glUniform4f(shader->getUniformLocation(mw::SHADER_U_VEC4_COLOR), 1, 1, 1, 1);
	drawFunction(sprite_);
	mw::glUniform4f(shader->getUniformLocation(mw::SHADER_U_VEC4_COLOR), 1, 0, 0, 1);
	text_.draw();
#else // MW_OPENGLES2
	// Update model matrix.
	glLoadIdentity();
	glTranslated(x_, y_, 0);
	glColor4d(1, 1, 1, 1);
	drawFunction(sprite_);
	glColor3d(1, 0, 0);
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
	auto shader = mw::Shader::getDefaultShader();
	shader->glUseProgram();
	mw::Matrix44 ortho = mw::getOrthoProjectionMatrix44(0, (float) w, 0, (float) h);
	// Update projection and model matrix.
	mw::glUniformMatrix4fv(mw::Shader::getDefaultShader()->getUniformLocation(mw::SHADER_U_MAT4_PROJ), 1, false, ortho.data());	
#else MW_OPENGLES2
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float) w, 0, (float) h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
#endif // MW_OPENGLES2
}
