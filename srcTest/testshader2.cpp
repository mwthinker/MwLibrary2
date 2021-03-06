#include "testshader2.h"

#include <mw/window.h>

TestShader2::TestShader2() {
    aPosIndex_ = -1;
    aTexIndex_ = -1;
	aColorIndex_ = -1;
	aTextureIndex_ = -1;

    // Collect the vertex buffer uniforms indexes.
    uProjIndex_ = -1;
    uModelIndex_ = -1;
}

TestShader2::TestShader2(std::string vShader, std::string fShader) {
	if (mw::Window::getOpenGlMajorVersion() >= 2) {
		shader_.bindAttribute("aPos");
		shader_.bindAttribute("aTex");
		shader_.bindAttribute("aColor");
		shader_.bindAttribute("aTexture");
		shader_.loadAndLinkFromFile(vShader, fShader);

		shader_.useProgram();

		// Collect the vertex buffer attributes indexes.
		aPosIndex_ = shader_.getAttributeLocation("aPos");
		aTexIndex_ = shader_.getAttributeLocation("aTex");
		aColorIndex_ = shader_.getAttributeLocation("aColor");
		aTextureIndex_ = shader_.getAttributeLocation("aTexture");

		// Collect the vertex buffer uniforms indexes.
		uProjIndex_ = shader_.getUniformLocation("uProj");
		uModelIndex_ = shader_.getUniformLocation("uModel");
	}
}

void TestShader2::useProgram() const {
	if (mw::Window::getOpenGlMajorVersion() >= 2) {
		shader_.useProgram();
	}
}

void TestShader2::setVertexAttribPointer() const {
	if (mw::Window::getOpenGlMajorVersion() >= 2) {
		size_t size = 0;

		glEnableVertexAttribArray(aPosIndex_);
		glVertexAttribPointer(aPosIndex_, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) size);
		size += sizeof(Vertex::pos_);

		glEnableVertexAttribArray(aTexIndex_);
		glVertexAttribPointer(aTexIndex_, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) size);
		size += sizeof(Vertex::tex_);

		glEnableVertexAttribArray(aColorIndex_);
		glVertexAttribPointer(aColorIndex_, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) size);
		size += sizeof(Vertex::color_);

		glEnableVertexAttribArray(aTextureIndex_);
		glVertexAttribPointer(aTextureIndex_, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) size);
		mw::checkGlError();
	}
}

// Uniforms. -------------------------------------------

void TestShader2::setProjectionMatrix(const mw::Matrix44<float>& matrix) const {
	if (mw::Window::getOpenGlMajorVersion() >= 2) {
		shader_.useProgram();
		glUniformMatrix4fv(uProjIndex_, 1, false, matrix.data());
	} else {
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(matrix.data());
		glMatrixMode(GL_MODELVIEW);
	}
}

void TestShader2::setModelMatrix(const mw::Matrix44<float>& matrix) const {
	if (mw::Window::getOpenGlMajorVersion() >= 2) {
		shader_.useProgram();
		glUniformMatrix4fv(uModelIndex_, 1, false, matrix.data());
	} else {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix.data());
	}
}
