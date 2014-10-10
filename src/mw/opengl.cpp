#include "opengl.h"
#include "matrix.h"

#include <SDL.h>

#include <cmath>
#include <iostream>

namespace mw {

	Matrix44 model_(I_44);
	Matrix44 proj_(I_44);

#if MW_OPENGLES2

	void _checkGlError(const char *file, int line) {
		GLenum err(glGetError());

		while (err != GL_NO_ERROR) {
			std::string error;

			switch (err) {
				case GL_INVALID_OPERATION:
					error = "INVALID_OPERATION";
					break;
				case GL_INVALID_ENUM:
					error = "INVALID_ENUM";
					break;
				case GL_INVALID_VALUE:
					error = "INVALID_VALUE";
					break;
				case GL_OUT_OF_MEMORY:
					error = "OUT_OF_MEMORY";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					error = "INVALID_FRAMEBUFFER_OPERATION";
					break;
			}
			
			std::cerr << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
			err = glGetError();
		}
	}

#else // MW_OPENGLES2

	void _checkGlError(const char *file, int line) {
		GLenum err(glGetError());

		while (err != GL_NO_ERROR) {
			std::string error;

			switch (err) {
				case GL_NO_ERROR:
					error = "GL_NO_ERROR";
					break;
				case GL_INVALID_ENUM:
					error = "GL_INVALID_ENUM";
					break;
				case GL_INVALID_VALUE:
					error = "GL_INVALID_VALUE";
					break;
				case GL_INVALID_OPERATION:
					error = "GL_INVALID_OPERATION";
					break;
				case GL_STACK_OVERFLOW:
					error = "GL_STACK_OVERFLOW";
					break;
				case GL_STACK_UNDERFLOW:
					error = "GL_STACK_UNDERFLOW";
					break;
				case GL_OUT_OF_MEMORY:
					error = "GL_OUT_OF_MEMORY";
					break;
			}

			std::cerr << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
			err = glGetError();
		}
	}

#endif // MW_OPENGLES2

	Matrix44 getTranslateMatrix44(float x, float y, float z) {
		return mw::Matrix44(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
	}

	Matrix44 getRotateMatrix44(float angle, float x, float y, float z) {
		float s = std::sin(angle);
		float c = std::cos(angle);

		return mw::Matrix44(
			x*x*(1 - c) + c, x*y*(1 - c) - z*s, x*z*(1 - c) + y*s, 0,
			y*x*(1 - c) + z*s, y*y*(1 - c) + c, y*z*(1 - c) - x*s, 0,
			z*x*(1 - c) - y*s, y*z*(1 - c) + x*s, z*z*(1 - c) + c, 0,
			0, 0, 0, 1);
	}

	Matrix44 getScaleMatrix44(float x, float y, float z) {
		return mw::Matrix44(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}

	Matrix44 getOrthoProjectionMatrix44(float left, float right, float bottom, float top, float near_, float far_) {
		return mw::Matrix44(
			2 / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, -2 / (far_ - near_), -(far_ + near_) / (far_ - near_),
			0, 0, 0, 1);
	}

	// Translate the matrix in the xy-plane.
	void translate2D(mw::Matrix44& matrix, float x, float y) {
		matrix(0, 3) += x;
		matrix(1, 3) += y;
	}
	
	void rotate2D(mw::Matrix44& matrix, float angle) {
		float s = std::sin(angle);
		float c = std::cos(angle);

		matrix(0, 0) = matrix(0, 0) *  c + matrix(0, 1) * s;
		matrix(0, 1) = matrix(0, 0) * -s + matrix(0, 1) * c;
		matrix(1, 0) = matrix(1, 0) *  c + matrix(1, 1) * s;
		matrix(1, 1) = matrix(1, 0) * -s + matrix(1, 1) * c;
	}

	void scale2D(mw::Matrix44& matrix, float sx, float sy) {
		matrix(0, 0) *= sx;
		matrix(1, 1) *= sy;
	}

	void ortho2D(mw::Matrix44& matrix, float left, float right, float bottom, float top) {
		matrix = mw::Matrix44(2 / (right - left), 0, -(right + left) / (right - left), 0,
							  0, 2 / (top - bottom), -(top + bottom) / (top - bottom), 0,
							  0, 0, 1, 0,
							  0, 0, 0, 1);
	}

#if MW_OPENGLES2

#define FUNC_POINTER_DEF(ret,func,params) ret (KHRONOS_APIENTRY *func) params = func;
	FUNC_POINTER_DEF(void, glActiveTexture, (GLenum))
		FUNC_POINTER_DEF(void, glAttachShader, (GLuint, GLuint))
		FUNC_POINTER_DEF(void, glBindAttribLocation, (GLuint, GLuint, const GLchar*))
		FUNC_POINTER_DEF(void, glBindBuffer, (GLenum, GLuint))
		FUNC_POINTER_DEF(void, glBindFramebuffer, (GLenum, GLuint))
		FUNC_POINTER_DEF(void, glBindRenderbuffer, (GLenum, GLuint))
		FUNC_POINTER_DEF(void, glBindTexture, (GLenum, GLuint))
		FUNC_POINTER_DEF(void, glBlendColor, (GLclampf, GLclampf, GLclampf, GLclampf))
		FUNC_POINTER_DEF(void, glBlendEquation, (GLenum))
		FUNC_POINTER_DEF(void, glBlendEquationSeparate, (GLenum, GLenum))
		FUNC_POINTER_DEF(void, glBlendFunc, (GLenum, GLenum))
		FUNC_POINTER_DEF(void, glBlendFuncSeparate, (GLenum, GLenum, GLenum, GLenum))
		FUNC_POINTER_DEF(void, glBufferData, (GLenum, GLsizeiptr, const GLvoid*, GLenum))
		FUNC_POINTER_DEF(void, glBufferSubData, (GLenum, GLintptr, GLsizeiptr, const GLvoid*))
		FUNC_POINTER_DEF(GLenum, glCheckFramebufferStatus, (GLenum))
		FUNC_POINTER_DEF(void, glClear, (GLbitfield))
		FUNC_POINTER_DEF(void, glClearColor, (GLclampf, GLclampf, GLclampf, GLclampf))
		FUNC_POINTER_DEF(void, glClearDepthf, (GLclampf))
		FUNC_POINTER_DEF(void, glClearStencil, (GLint))
		FUNC_POINTER_DEF(void, glColorMask, (GLboolean, GLboolean, GLboolean, GLboolean))
		FUNC_POINTER_DEF(void, glCompileShader, (GLuint))
		FUNC_POINTER_DEF(void, glCompressedTexImage2D, (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*))
		FUNC_POINTER_DEF(void, glCompressedTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*))
		FUNC_POINTER_DEF(void, glCopyTexImage2D, (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint))
		FUNC_POINTER_DEF(void, glCopyTexSubImage2D, (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei))
		FUNC_POINTER_DEF(GLuint, glCreateProgram, (void))
		FUNC_POINTER_DEF(GLuint, glCreateShader, (GLenum))
		FUNC_POINTER_DEF(void, glCullFace, (GLenum))
		FUNC_POINTER_DEF(void, glDeleteBuffers, (GLsizei, const GLuint*))
		FUNC_POINTER_DEF(void, glDeleteFramebuffers, (GLsizei, const GLuint*))
		FUNC_POINTER_DEF(void, glDeleteProgram, (GLuint))
		FUNC_POINTER_DEF(void, glDeleteRenderbuffers, (GLsizei, const GLuint*))
		FUNC_POINTER_DEF(void, glDeleteShader, (GLuint))
		FUNC_POINTER_DEF(void, glDeleteTextures, (GLsizei, const GLuint*))
		FUNC_POINTER_DEF(void, glDepthFunc, (GLenum))
		FUNC_POINTER_DEF(void, glDepthMask, (GLboolean))
		FUNC_POINTER_DEF(void, glDepthRangef, (GLclampf, GLclampf))
		FUNC_POINTER_DEF(void, glDetachShader, (GLuint, GLuint))
		FUNC_POINTER_DEF(void, glDisable, (GLenum))
		FUNC_POINTER_DEF(void, glDisableVertexAttribArray, (GLuint))
		FUNC_POINTER_DEF(void, glDrawArrays, (GLenum, GLint, GLsizei))
		FUNC_POINTER_DEF(void, glDrawElements, (GLenum, GLsizei, GLenum, const GLvoid*))
		FUNC_POINTER_DEF(void, glEnable, (GLenum))
		FUNC_POINTER_DEF(void, glEnableVertexAttribArray, (GLuint))
		FUNC_POINTER_DEF(void, glFinish, (void))
		FUNC_POINTER_DEF(void, glFlush, (void))
		FUNC_POINTER_DEF(void, glFramebufferRenderbuffer, (GLenum, GLenum, GLenum, GLuint))
		FUNC_POINTER_DEF(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint))
		FUNC_POINTER_DEF(void, glFrontFace, (GLenum))
		FUNC_POINTER_DEF(void, glGenBuffers, (GLsizei, GLuint*))
		FUNC_POINTER_DEF(void, glGenerateMipmap, (GLenum))
		FUNC_POINTER_DEF(void, glGenFramebuffers, (GLsizei, GLuint*))
		FUNC_POINTER_DEF(void, glGenRenderbuffers, (GLsizei, GLuint*))
		FUNC_POINTER_DEF(void, glGenTextures, (GLsizei, GLuint*))
		FUNC_POINTER_DEF(void, glGetActiveAttrib, (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*))
		FUNC_POINTER_DEF(void, glGetActiveUniform, (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*))
		FUNC_POINTER_DEF(void, glGetAttachedShaders, (GLuint, GLsizei, GLsizei*, GLuint*))
		FUNC_POINTER_DEF(int, glGetAttribLocation, (GLuint, const GLchar*))
		FUNC_POINTER_DEF(void, glGetBooleanv, (GLenum, GLboolean*))
		FUNC_POINTER_DEF(void, glGetBufferParameteriv, (GLenum, GLenum, GLint*))
		FUNC_POINTER_DEF(GLenum, glGetError, (void))
		FUNC_POINTER_DEF(void, glGetFloatv, (GLenum, GLfloat*))
		FUNC_POINTER_DEF(void, glGetFramebufferAttachmentParameteriv, (GLenum, GLenum, GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetIntegerv, (GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetProgramiv, (GLuint, GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetProgramInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
		FUNC_POINTER_DEF(void, glGetRenderbufferParameteriv, (GLenum, GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetShaderiv, (GLuint, GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
		FUNC_POINTER_DEF(void, glGetShaderPrecisionFormat, (GLenum, GLenum, GLint*, GLint*))
		FUNC_POINTER_DEF(void, glGetShaderSource, (GLuint, GLsizei, GLsizei*, GLchar*))
		FUNC_POINTER_DEF(const GLubyte*, glGetString, (GLenum))
		FUNC_POINTER_DEF(void, glGetTexParameterfv, (GLenum  GLenum, GLfloat*))
		FUNC_POINTER_DEF(void, glGetTexParameteriv, (GLenum, GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetUniformfv, (GLuint, GLint, GLfloat*))
		FUNC_POINTER_DEF(void, glGetUniformiv, (GLuint, GLint, GLint*))
		FUNC_POINTER_DEF(int, glGetUniformLocation, (GLuint, const GLchar*))
		FUNC_POINTER_DEF(void, glGetVertexAttribfv, (GLuint, GLenum, GLfloat*))
		FUNC_POINTER_DEF(void, glGetVertexAttribiv, (GLuint, GLenum, GLint*))
		FUNC_POINTER_DEF(void, glGetVertexAttribPointerv, (GLuint, GLenum, GLvoid**))
		FUNC_POINTER_DEF(void, glHint, (GLenum, GLenum))
		FUNC_POINTER_DEF(GLboolean, glIsBuffer, (GLuint))
		FUNC_POINTER_DEF(GLboolean, glIsEnabled, (GLenum))
		FUNC_POINTER_DEF(GLboolean, glIsFramebuffer, (GLuint))
		FUNC_POINTER_DEF(GLboolean, glIsProgram, (GLuint))
		FUNC_POINTER_DEF(GLboolean, glIsRenderbuffer, (GLuint))
		FUNC_POINTER_DEF(GLboolean, glIsShader, (GLuint))
		FUNC_POINTER_DEF(GLboolean, glIsTexture, (GLuint))
		FUNC_POINTER_DEF(void, glLineWidth, (GLfloat))
		FUNC_POINTER_DEF(void, glLinkProgram, (GLuint))
		FUNC_POINTER_DEF(void, glPixelStorei, (GLenum, GLint))
		FUNC_POINTER_DEF(void, glPolygonOffset, (GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glReadPixels, (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*))
		FUNC_POINTER_DEF(void, glReleaseShaderCompiler, (void))
		FUNC_POINTER_DEF(void, glRenderbufferStorage, (GLenum, GLenum, GLsizei, GLsizei))
		FUNC_POINTER_DEF(void, glSampleCoverage, (GLclampf, GLboolean))
		FUNC_POINTER_DEF(void, glScissor, (GLint, GLint, GLsizei, GLsizei))
		FUNC_POINTER_DEF(void, glShaderBinary, (GLsizei, const GLuint*, GLenum, const GLvoid*, GLsizei))
		FUNC_POINTER_DEF(void, glShaderSource, (GLuint, GLsizei, const GLchar* const*, const GLint*))
		FUNC_POINTER_DEF(void, glStencilFunc, (GLenum, GLint, GLuint))
		FUNC_POINTER_DEF(void, glStencilFuncSeparate, (GLenum, GLenum, GLint, GLuint))
		FUNC_POINTER_DEF(void, glStencilMask, (GLuint))
		FUNC_POINTER_DEF(void, glStencilMaskSeparate, (GLenum, GLuint))
		FUNC_POINTER_DEF(void, glStencilOp, (GLenum, GLenum, GLenum))
		FUNC_POINTER_DEF(void, glStencilOpSeparate, (GLenum, GLenum, GLenum, GLenum))
		FUNC_POINTER_DEF(void, glTexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*))
		FUNC_POINTER_DEF(void, glTexParameterf, (GLenum, GLenum, GLfloat))
		FUNC_POINTER_DEF(void, glTexParameterfv, (GLenum, GLenum, const GLfloat*))
		FUNC_POINTER_DEF(void, glTexParameteri, (GLenum, GLenum, GLint))
		FUNC_POINTER_DEF(void, glTexParameteriv, (GLenum, GLenum, const GLint*))
		FUNC_POINTER_DEF(void, glTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*))
		FUNC_POINTER_DEF(void, glUniform1f, (GLint, GLfloat))
		FUNC_POINTER_DEF(void, glUniform1fv, (GLint, GLsizei, const GLfloat*))
		FUNC_POINTER_DEF(void, glUniform1i, (GLint, GLint))
		FUNC_POINTER_DEF(void, glUniform1iv, (GLint, GLsizei, const GLint*))
		FUNC_POINTER_DEF(void, glUniform2f, (GLint, GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glUniform2fv, (GLint, GLsizei, const GLfloat*))
		FUNC_POINTER_DEF(void, glUniform2i, (GLint, GLint, GLint))
		FUNC_POINTER_DEF(void, glUniform2iv, (GLint, GLsizei, const GLint*))
		FUNC_POINTER_DEF(void, glUniform3f, (GLint, GLfloat, GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glUniform3fv, (GLint, GLsizei, const GLfloat*))
		FUNC_POINTER_DEF(void, glUniform3i, (GLint, GLint, GLint, GLint))
		FUNC_POINTER_DEF(void, glUniform3iv, (GLint, GLsizei, const GLint*))
		FUNC_POINTER_DEF(void, glUniform4f, (GLint, GLfloat, GLfloat, GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glUniform4fv, (GLint, GLsizei, const GLfloat*))
		FUNC_POINTER_DEF(void, glUniform4i, (GLint, GLint, GLint, GLint, GLint))
		FUNC_POINTER_DEF(void, glUniform4iv, (GLint, GLsizei, const GLint*))
		FUNC_POINTER_DEF(void, glUniformMatrix2fv, (GLint, GLsizei, GLboolean, const GLfloat*))
		FUNC_POINTER_DEF(void, glUniformMatrix3fv, (GLint, GLsizei, GLboolean, const GLfloat*))
		FUNC_POINTER_DEF(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat*))
		FUNC_POINTER_DEF(void, glUseProgram, (GLuint))
		FUNC_POINTER_DEF(void, glValidateProgram, (GLuint))
		FUNC_POINTER_DEF(void, glVertexAttrib1f, (GLuint, GLfloat))
		FUNC_POINTER_DEF(void, glVertexAttrib1fv, (GLuint, const GLfloat*))
		FUNC_POINTER_DEF(void, glVertexAttrib2f, (GLuint, GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glVertexAttrib2fv, (GLuint, const GLfloat*))
		FUNC_POINTER_DEF(void, glVertexAttrib3f, (GLuint, GLfloat, GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glVertexAttrib3fv, (GLuint, const GLfloat*))
		FUNC_POINTER_DEF(void, glVertexAttrib4f, (GLuint, GLfloat, GLfloat, GLfloat, GLfloat))
		FUNC_POINTER_DEF(void, glVertexAttrib4fv, (GLuint, const GLfloat*))
		FUNC_POINTER_DEF(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*))
		FUNC_POINTER_DEF(void, glViewport, (GLint, GLint, GLsizei, GLsizei))
#undef FuncPointer

#define FUNC_POINTER_LINC(ret,func,params) func = (ret (KHRONOS_APIENTRY*)params) SDL_GL_GetProcAddress(#func);
		void initGLES2() {
		FUNC_POINTER_LINC(void, glActiveTexture, (GLenum))
			FUNC_POINTER_LINC(void, glAttachShader, (GLuint, GLuint))
			FUNC_POINTER_LINC(void, glBindAttribLocation, (GLuint, GLuint, const GLchar*))
			FUNC_POINTER_LINC(void, glBindBuffer, (GLenum, GLuint))
			FUNC_POINTER_LINC(void, glBindFramebuffer, (GLenum, GLuint))
			FUNC_POINTER_LINC(void, glBindRenderbuffer, (GLenum, GLuint))
			FUNC_POINTER_LINC(void, glBindTexture, (GLenum, GLuint))
			FUNC_POINTER_LINC(void, glBlendColor, (GLclampf, GLclampf, GLclampf, GLclampf))
			FUNC_POINTER_LINC(void, glBlendEquation, (GLenum))
			FUNC_POINTER_LINC(void, glBlendEquationSeparate, (GLenum, GLenum))
			FUNC_POINTER_LINC(void, glBlendFunc, (GLenum, GLenum))
			FUNC_POINTER_LINC(void, glBlendFuncSeparate, (GLenum, GLenum, GLenum, GLenum))
			FUNC_POINTER_LINC(void, glBufferData, (GLenum, GLsizeiptr, const GLvoid*, GLenum))
			FUNC_POINTER_LINC(void, glBufferSubData, (GLenum, GLintptr, GLsizeiptr, const GLvoid*))
			FUNC_POINTER_LINC(GLenum, glCheckFramebufferStatus, (GLenum))
			FUNC_POINTER_LINC(void, glClear, (GLbitfield))
			FUNC_POINTER_LINC(void, glClearColor, (GLclampf, GLclampf, GLclampf, GLclampf))
			FUNC_POINTER_LINC(void, glClearDepthf, (GLclampf))
			FUNC_POINTER_LINC(void, glClearStencil, (GLint))
			FUNC_POINTER_LINC(void, glColorMask, (GLboolean, GLboolean, GLboolean, GLboolean))
			FUNC_POINTER_LINC(void, glCompileShader, (GLuint))
			FUNC_POINTER_LINC(void, glCompressedTexImage2D, (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*))
			FUNC_POINTER_LINC(void, glCompressedTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*))
			FUNC_POINTER_LINC(void, glCopyTexImage2D, (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint))
			FUNC_POINTER_LINC(void, glCopyTexSubImage2D, (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei))
			FUNC_POINTER_LINC(GLuint, glCreateProgram, (void))
			FUNC_POINTER_LINC(GLuint, glCreateShader, (GLenum))
			FUNC_POINTER_LINC(void, glCullFace, (GLenum))
			FUNC_POINTER_LINC(void, glDeleteBuffers, (GLsizei, const GLuint*))
			FUNC_POINTER_LINC(void, glDeleteFramebuffers, (GLsizei, const GLuint*))
			FUNC_POINTER_LINC(void, glDeleteProgram, (GLuint))
			FUNC_POINTER_LINC(void, glDeleteRenderbuffers, (GLsizei, const GLuint*))
			FUNC_POINTER_LINC(void, glDeleteShader, (GLuint))
			FUNC_POINTER_LINC(void, glDeleteTextures, (GLsizei, const GLuint*))
			FUNC_POINTER_LINC(void, glDepthFunc, (GLenum))
			FUNC_POINTER_LINC(void, glDepthMask, (GLboolean))
			FUNC_POINTER_LINC(void, glDepthRangef, (GLclampf, GLclampf))
			FUNC_POINTER_LINC(void, glDetachShader, (GLuint, GLuint))
			FUNC_POINTER_LINC(void, glDisable, (GLenum))
			FUNC_POINTER_LINC(void, glDisableVertexAttribArray, (GLuint))
			FUNC_POINTER_LINC(void, glDrawArrays, (GLenum, GLint, GLsizei))
			FUNC_POINTER_LINC(void, glDrawElements, (GLenum, GLsizei, GLenum, const GLvoid*))
			FUNC_POINTER_LINC(void, glEnable, (GLenum))
			FUNC_POINTER_LINC(void, glEnableVertexAttribArray, (GLuint))
			FUNC_POINTER_LINC(void, glFinish, (void))
			FUNC_POINTER_LINC(void, glFlush, (void))
			FUNC_POINTER_LINC(void, glFramebufferRenderbuffer, (GLenum, GLenum, GLenum, GLuint))
			FUNC_POINTER_LINC(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint))
			FUNC_POINTER_LINC(void, glFrontFace, (GLenum))
			FUNC_POINTER_LINC(void, glGenBuffers, (GLsizei, GLuint*))
			FUNC_POINTER_LINC(void, glGenerateMipmap, (GLenum))
			FUNC_POINTER_LINC(void, glGenFramebuffers, (GLsizei, GLuint*))
			FUNC_POINTER_LINC(void, glGenRenderbuffers, (GLsizei, GLuint*))
			FUNC_POINTER_LINC(void, glGenTextures, (GLsizei, GLuint*))
			FUNC_POINTER_LINC(void, glGetActiveAttrib, (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*))
			FUNC_POINTER_LINC(void, glGetActiveUniform, (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*))
			FUNC_POINTER_LINC(void, glGetAttachedShaders, (GLuint, GLsizei, GLsizei*, GLuint*))
			FUNC_POINTER_LINC(int, glGetAttribLocation, (GLuint, const GLchar*))
			FUNC_POINTER_LINC(void, glGetBooleanv, (GLenum, GLboolean*))
			FUNC_POINTER_LINC(void, glGetBufferParameteriv, (GLenum, GLenum, GLint*))
			FUNC_POINTER_LINC(GLenum, glGetError, (void))
			FUNC_POINTER_LINC(void, glGetFloatv, (GLenum, GLfloat*))
			FUNC_POINTER_LINC(void, glGetFramebufferAttachmentParameteriv, (GLenum, GLenum, GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetIntegerv, (GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetProgramiv, (GLuint, GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetProgramInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
			FUNC_POINTER_LINC(void, glGetRenderbufferParameteriv, (GLenum, GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetShaderiv, (GLuint, GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
			FUNC_POINTER_LINC(void, glGetShaderPrecisionFormat, (GLenum, GLenum, GLint*, GLint*))
			FUNC_POINTER_LINC(void, glGetShaderSource, (GLuint, GLsizei, GLsizei*, GLchar*))
			FUNC_POINTER_LINC(const GLubyte*, glGetString, (GLenum))
			FUNC_POINTER_LINC(void, glGetTexParameterfv, (GLenum  GLenum, GLfloat*))
			FUNC_POINTER_LINC(void, glGetTexParameteriv, (GLenum, GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetUniformfv, (GLuint, GLint, GLfloat*))
			FUNC_POINTER_LINC(void, glGetUniformiv, (GLuint, GLint, GLint*))
			FUNC_POINTER_LINC(int, glGetUniformLocation, (GLuint, const GLchar*))
			FUNC_POINTER_LINC(void, glGetVertexAttribfv, (GLuint, GLenum, GLfloat*))
			FUNC_POINTER_LINC(void, glGetVertexAttribiv, (GLuint, GLenum, GLint*))
			FUNC_POINTER_LINC(void, glGetVertexAttribPointerv, (GLuint, GLenum, GLvoid**))
			FUNC_POINTER_LINC(void, glHint, (GLenum, GLenum))
			FUNC_POINTER_LINC(GLboolean, glIsBuffer, (GLuint))
			FUNC_POINTER_LINC(GLboolean, glIsEnabled, (GLenum))
			FUNC_POINTER_LINC(GLboolean, glIsFramebuffer, (GLuint))
			FUNC_POINTER_LINC(GLboolean, glIsProgram, (GLuint))
			FUNC_POINTER_LINC(GLboolean, glIsRenderbuffer, (GLuint))
			FUNC_POINTER_LINC(GLboolean, glIsShader, (GLuint))
			FUNC_POINTER_LINC(GLboolean, glIsTexture, (GLuint))
			FUNC_POINTER_LINC(void, glLineWidth, (GLfloat))
			FUNC_POINTER_LINC(void, glLinkProgram, (GLuint))
			FUNC_POINTER_LINC(void, glPixelStorei, (GLenum, GLint))
			FUNC_POINTER_LINC(void, glPolygonOffset, (GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glReadPixels, (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*))
			FUNC_POINTER_LINC(void, glReleaseShaderCompiler, (void))
			FUNC_POINTER_LINC(void, glRenderbufferStorage, (GLenum, GLenum, GLsizei, GLsizei))
			FUNC_POINTER_LINC(void, glSampleCoverage, (GLclampf, GLboolean))
			FUNC_POINTER_LINC(void, glScissor, (GLint, GLint, GLsizei, GLsizei))
			FUNC_POINTER_LINC(void, glShaderBinary, (GLsizei, const GLuint*, GLenum, const GLvoid*, GLsizei))
			FUNC_POINTER_LINC(void, glShaderSource, (GLuint, GLsizei, const GLchar* const*, const GLint*))
			FUNC_POINTER_LINC(void, glStencilFunc, (GLenum, GLint, GLuint))
			FUNC_POINTER_LINC(void, glStencilFuncSeparate, (GLenum, GLenum, GLint, GLuint))
			FUNC_POINTER_LINC(void, glStencilMask, (GLuint))
			FUNC_POINTER_LINC(void, glStencilMaskSeparate, (GLenum, GLuint))
			FUNC_POINTER_LINC(void, glStencilOp, (GLenum, GLenum, GLenum))
			FUNC_POINTER_LINC(void, glStencilOpSeparate, (GLenum, GLenum, GLenum, GLenum))
			FUNC_POINTER_LINC(void, glTexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*))
			FUNC_POINTER_LINC(void, glTexParameterf, (GLenum, GLenum, GLfloat))
			FUNC_POINTER_LINC(void, glTexParameterfv, (GLenum, GLenum, const GLfloat*))
			FUNC_POINTER_LINC(void, glTexParameteri, (GLenum, GLenum, GLint))
			FUNC_POINTER_LINC(void, glTexParameteriv, (GLenum, GLenum, const GLint*))
			FUNC_POINTER_LINC(void, glTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*))
			FUNC_POINTER_LINC(void, glUniform1f, (GLint, GLfloat))
			FUNC_POINTER_LINC(void, glUniform1fv, (GLint, GLsizei, const GLfloat*))
			FUNC_POINTER_LINC(void, glUniform1i, (GLint, GLint))
			FUNC_POINTER_LINC(void, glUniform1iv, (GLint, GLsizei, const GLint*))
			FUNC_POINTER_LINC(void, glUniform2f, (GLint, GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glUniform2fv, (GLint, GLsizei, const GLfloat*))
			FUNC_POINTER_LINC(void, glUniform2i, (GLint, GLint, GLint))
			FUNC_POINTER_LINC(void, glUniform2iv, (GLint, GLsizei, const GLint*))
			FUNC_POINTER_LINC(void, glUniform3f, (GLint, GLfloat, GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glUniform3fv, (GLint, GLsizei, const GLfloat*))
			FUNC_POINTER_LINC(void, glUniform3i, (GLint, GLint, GLint, GLint))
			FUNC_POINTER_LINC(void, glUniform3iv, (GLint, GLsizei, const GLint*))
			FUNC_POINTER_LINC(void, glUniform4f, (GLint, GLfloat, GLfloat, GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glUniform4fv, (GLint, GLsizei, const GLfloat*))
			FUNC_POINTER_LINC(void, glUniform4i, (GLint, GLint, GLint, GLint, GLint))
			FUNC_POINTER_LINC(void, glUniform4iv, (GLint, GLsizei, const GLint*))
			FUNC_POINTER_LINC(void, glUniformMatrix2fv, (GLint, GLsizei, GLboolean, const GLfloat*))
			FUNC_POINTER_LINC(void, glUniformMatrix3fv, (GLint, GLsizei, GLboolean, const GLfloat*))
			FUNC_POINTER_LINC(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat*))
			FUNC_POINTER_LINC(void, glUseProgram, (GLuint))
			FUNC_POINTER_LINC(void, glValidateProgram, (GLuint))
			FUNC_POINTER_LINC(void, glVertexAttrib1f, (GLuint, GLfloat))
			FUNC_POINTER_LINC(void, glVertexAttrib1fv, (GLuint, const GLfloat*))
			FUNC_POINTER_LINC(void, glVertexAttrib2f, (GLuint, GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glVertexAttrib2fv, (GLuint, const GLfloat*))
			FUNC_POINTER_LINC(void, glVertexAttrib3f, (GLuint, GLfloat, GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glVertexAttrib3fv, (GLuint, const GLfloat*))
			FUNC_POINTER_LINC(void, glVertexAttrib4f, (GLuint, GLfloat, GLfloat, GLfloat, GLfloat))
			FUNC_POINTER_LINC(void, glVertexAttrib4fv, (GLuint, const GLfloat*))
			FUNC_POINTER_LINC(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*))
			FUNC_POINTER_LINC(void, glViewport, (GLint, GLint, GLsizei, GLsizei))
	}
#undef FUNC_POINTER_LINC

#endif // MW_OPENGLES2

} // Namespace mw.
