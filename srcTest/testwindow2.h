#ifndef TESTWINDOW2_H
#define TESTWINDOW2_H

#include <mw/window.h>
#include <mw/opengl.h>

static GLuint loadShader(GLuint program, GLenum type, const GLchar *shaderSrc) {
	GLuint shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);
	glAttachShader(program, shader);
	return 0;
}

static const GLchar vertex[] =
	"#version 100\n"
	"precision mediump float;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n"
	"   gl_PointSize = 128.0;\n"
	"}\0";

static const GLchar fragment[] =
	"#version 100\n"
	"precision mediump float;\n"
	"void main()\n"
	"{\n"
	"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\0";

class TestWindow2 : public mw::Window {
public:
	TestWindow2() : mw::Window(600, 600, true, "Test") {
		//GLuint programObject = glCreateProgram();
		//loadShader(programObject, GL_VERTEX_SHADER, vertex);
		//loadShader(programObject, GL_FRAGMENT_SHADER, fragment);
		//glLinkProgram(programObject);
		//glUseProgram(programObject);
	}

	void update(Uint32 msDeltaTime) override {
		glDrawArrays(GL_POINTS, 0, 1);
		//glGenBuffers();
		//glBindBuffer(GL_ARRAY_BUFFER,)
	}

	void eventUpdate(const SDL_Event& windowEvent) override {
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
				}
				break;
		}
	}

private:
};

#endif // TESTWINDOW2_H
