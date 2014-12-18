#ifndef MW_DEFAULTSHADER_H
#define MW_DEFAULTSHADER_H
#if MW_OPENGLES2

#include <mw/opengl.h>
#include <mw/matrix.h>
#include <mw/shader.h>
#include <mw/color.h>

namespace mw {

	static const std::string DEFAULT_SHADER_VER =
		"#version 100\n"
		""
		"precision mediump float;\n"
		""
		"uniform mat4 uModel;\n"
		"uniform mat4 uProj;\n"
		"uniform float uIsTexture;\n"
		""
		"attribute vec4 aPos;\n"
		"attribute vec2 aTex;\n"
		""
		"varying vec2 vTexCoord;\n"
		""
		"void main() {"
		"	gl_Position = uProj * uModel * aPos;"
		"	if (uIsTexture > 0.5) {"
		"		vTexCoord = aTex;"
		"	}"
		"}";

	static const std::string DEFAULT_SHADER_FRAG =
		"#version 100\n"
		""
		"precision mediump float;\n"
		""
		"uniform sampler2D uTexture;\n"
		"uniform vec4 uColor;\n"
		"uniform float uIsTexture;\n"
		""
		"varying vec2 vTexCoord;\n"
		""
		"void main() {"
		""
		"	if (uIsTexture < 0.5) {"
		"		gl_FragColor = uColor;"
		"	} else {"
		"		vec4 tex = texture2D(uTexture, vTexCoord); "
		"		gl_FragColor = vec4(uColor.x * tex.x, uColor.y * tex.y, uColor.z * tex.z, uColor.a * tex.a);"
		"	}"
		"}";

	class DefaultShader {
	public:
		friend class Window;

		DefaultShader();
		DefaultShader(std::string vShader, std::string fShader);

		void glUseProgram() const;

		// Vertex buffer Attributes. ---------------------------
		
		void setGlPosA(GLint size, const GLvoid* data) const;
		void setGlPosA(GLint size, GLsizei stride, const GLvoid* data) const;

		void setGlTexA(GLint size, const GLvoid* data) const;
		void setGlTexA(GLint size, GLsizei stride, const GLvoid* data) const;

		// Uniforms. -------------------------------------------

		void setGlProjectionMatrixU(const mw::Matrix44& matrix) const;
		void setGlModelMatrixU(const mw::Matrix44& matrix) const;

		void setGlColorU(float red, float green, float blue, float alpha = 1) const;
		void setGlColorU(const mw::Color& color) const;
		void setGlTextureU(bool texture) const;

		static const DefaultShader& getCurrent();

	private:
		mw::Shader shader_;
		
		int aPosIndex_;
		int aTexIndex_;
		
		int uProjIndex_;
		int uModelIndex_;
		int uColorIndex_;
		int uIsTexIndex_;

		static DefaultShader defaultShader;
	};

} // Namespace mw.

#endif // MW_OPENGLES2
#endif // MW_DEFAULTSHADER_H
