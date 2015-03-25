#include "testshader.h"

TestShader::TestShader() {
    aPosIndex_ = -1;
    aTexIndex_ = -1;

    // Collect the vertex buffer uniforms indexes.
    uProjIndex_ = -1;
    uModelIndex_ = -1;

    // Collect the fragment buffer uniforms indexes.
    uColorIndex_ = -1;
    uIsTexIndex_ = -1;
}

TestShader::TestShader(std::string vShader, std::string fShader) {
    shader_.bindAttribute("aPos");
    shader_.bindAttribute("aTex");
    shader_.loadAndLink(vShader, fShader);

    shader_.glUseProgram();

    // Collect the vertex buffer attributes indexes.
    aPosIndex_ = shader_.getAttributeLocation("aPos");
    aTexIndex_ = shader_.getAttributeLocation("aTex");

    // Collect the vertex buffer uniforms indexes.
    uProjIndex_ = shader_.getUniformLocation("uProj");
    uModelIndex_ = shader_.getUniformLocation("uModel");

    // Collect the fragment buffer uniforms indexes.
    uColorIndex_ = shader_.getUniformLocation("uColor");
    uIsTexIndex_ = shader_.getUniformLocation("uIsTexture");
}

void TestShader::glUseProgram() const {
    shader_.glUseProgram();
}

// Vertex buffer Attributes. ---------------------------

void TestShader::setGlPosA(GLint size, const GLvoid* data) const {
    glEnableVertexAttribArray(aPosIndex_);
    glVertexAttribPointer(aPosIndex_, size, GL_FLOAT, GL_FALSE, 0, data);
}

void TestShader::setGlPosA(GLint size, GLsizei stride, const GLvoid* data) const {
    glEnableVertexAttribArray(aPosIndex_);
    glVertexAttribPointer(aPosIndex_, size, GL_FLOAT, GL_FALSE, stride, data);
}

void TestShader::setGlTexA(GLint size, const GLvoid* data) const {
    glEnableVertexAttribArray(aTexIndex_);
    glVertexAttribPointer(aTexIndex_, size, GL_FLOAT, GL_FALSE, 0, data);
}

void TestShader::setGlTexA(GLint size, GLsizei stride, const GLvoid* data) const {
    glEnableVertexAttribArray(aTexIndex_);
    glVertexAttribPointer(aTexIndex_, size, GL_FLOAT, GL_FALSE, stride, data);
}

// Uniforms. -------------------------------------------

void TestShader::setGlProjectionMatrixU(const mw::Matrix44& matrix) const {
    glUniformMatrix4fv(uProjIndex_, 1, false, matrix.data());
}

void TestShader::setGlModelMatrixU(const mw::Matrix44& matrix) const {
    glUniformMatrix4fv(uModelIndex_, 1, false, matrix.data());
}

void TestShader::setGlColorU(float red, float green, float blue, float alpha) const {
    glUniform4f(uColorIndex_, red, green, blue, alpha);
}

void TestShader::setGlColorU(const mw::Color& color) const {
    glUniform4f(uColorIndex_, color.red_, color.green_, color.blue_, color.alpha_);
}

void TestShader::setGlTextureU(bool texture) const {
    if (texture) {
        glUniform1f(uIsTexIndex_, 1);
    } else {
        glUniform1f(uIsTexIndex_, 0);
    }
}