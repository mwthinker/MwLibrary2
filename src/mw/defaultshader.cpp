#if MW_OPENGLES2
#include "defaultshader.h"

namespace mw {

	DefaultShader::DefaultShader() {
		aPosIndex_ = -1;
		aTexIndex_ = -1;

		// Collect the vertex buffer uniforms indexes.
		uProjIndex_ = -1;
		uModelIndex_ = -1;

		// Collect the fragment buffer uniforms indexes.
		uColorIndex_ = -1;
		uIsTexIndex_ = -1;
	}

	DefaultShader::DefaultShader(std::string vShaderFile, std::string fShaderFile) {
		shader_.bindAttribute("aPos");
		shader_.bindAttribute("aTex");
		shader_.loadAndLink(vShaderFile, fShaderFile);
		
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

	void DefaultShader::glUseProgram() const {
		shader_.glUseProgram();
	}

	// Vertex buffer Attributes. ---------------------------

	void DefaultShader::setGlPosA(GLint size, const GLvoid* data) const {
		mw::glVertexAttribPointer(aPosIndex_, size, GL_FLOAT, GL_FALSE, 0, data);
		mw::glEnableVertexAttribArray(aPosIndex_);
	}

	void DefaultShader::setGlPosA(GLint size, GLsizei stride, const GLvoid* data) const {
		mw::glVertexAttribPointer(aPosIndex_, size, GL_FLOAT, GL_FALSE, stride, data);
		mw::glEnableVertexAttribArray(aPosIndex_);
	}

	void DefaultShader::setGlTexA(GLint size, const GLvoid* data) const {
		mw::glVertexAttribPointer(aTexIndex_, 2, GL_FLOAT, GL_FALSE, 0, data);
		mw::glEnableVertexAttribArray(aTexIndex_);
	}

	void DefaultShader::setGlTexA(GLint size, GLsizei stride, const GLvoid* data) const {
		mw::glVertexAttribPointer(aTexIndex_, 2, GL_FLOAT, GL_FALSE, stride, data);
		mw::glEnableVertexAttribArray(aTexIndex_);
	}	

	// Uniforms. -------------------------------------------

	void DefaultShader::setGlProjectionMatrixU(const mw::Matrix44& matrix) const {
		mw::glUniformMatrix4fv(uProjIndex_, 1, false, matrix.data());
	}

	void DefaultShader::setGlModelMatrixU(const mw::Matrix44& matrix) const {
		mw::glUniformMatrix4fv(uModelIndex_, 1, false, matrix.data());
	}

	void DefaultShader::setGlColorU(float red, float green, float blue, float alpha) const {
		mw::glUniform4f(uColorIndex_, red, green, blue, alpha);
	}

	void DefaultShader::setGlColorU(const mw::Color& color) const {
		mw::glUniform4f(uColorIndex_, color.red_, color.green_, color.blue_, color.alpha_);
	}	

	void DefaultShader::setGlTextureU(bool texture) const {
		if (texture) {
			mw::glUniform1f(uIsTexIndex_, 1);
		} else {
			mw::glUniform1f(uIsTexIndex_, 0);
		}
	}

	DefaultShader DefaultShader::defaultShader;

	const DefaultShader& DefaultShader::getCurrent() {
		return defaultShader;
	}

} // Namespace mw.

#endif // MW_OPENGLES2
