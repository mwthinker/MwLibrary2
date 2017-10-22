#ifndef TESTSHADER2_H
#define TESTSHADER2_H

#include <mw/opengl.h>
#include <mw/vertexarrayobject.h>
#include <mw/shader.h>

#include <mw/matrix44.h>
#include <mw/vec2.h>
#include <mw/color.h>

#include <string>

class TestShader2 {
public:
	TestShader2();
	TestShader2(std::string vShader, std::string fShader);

	void useProgram() const;
	void setVertexAttribPointer() const;

	// Uniforms. -------------------------------------------

	void setProjectionMatrix(const mw::Matrix44<float>& matrix) const;
	void setModelMatrix(const mw::Matrix44<float>& matrix) const;

	class Vertex {
	public:
		Vertex() = default;

		Vertex(GLfloat x, GLfloat y) : pos_(x, y), color_(1, 1, 1, 1), texture_(0) {
		}

		Vertex(GLfloat x, GLfloat y, GLfloat xTex, GLfloat yTex) : pos_(x, y), tex_(xTex, yTex), color_(1, 1, 1, 1), texture_(1.f) {
		}

		mw::Vec2<GLfloat> pos_;
		mw::Vec2<GLfloat> tex_;
		mw::Color color_;
		GLfloat texture_;
	};

private:
	mw::Shader shader_;

	int aPosIndex_;
	int aTexIndex_;
	int aColorIndex_;
	int aTextureIndex_;

	int uProjIndex_;
	int uModelIndex_;
};

#endif // TESTSHADER2_H
