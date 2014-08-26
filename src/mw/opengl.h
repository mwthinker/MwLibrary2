#ifndef MW_OPENGL_H
#define MW_OPENGL_H

#if MW_OPENGLES2
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <string>

namespace mw {

#if MW_OPENGLES2

	static const std::string SHADER_VER =
		"#version 100\n"
		""
		"precision mediump float;\n"
		""
		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uProjectionMatrix;\n"
		""
		"attribute vec4 aPosition;\n"
		"attribute vec2 aTexCoord;\n"
		""
		"varying vec2 vTexCoord;\n"
		""
		"void main() {"
		"	gl_Position = uProjectionMatrix * uModelMatrix * aPosition;"
		"	vTexCoord = aTexCoord;"
		"}";

	static const std::string SHADER_FRAG =
		"#version 100\n"
		""
		"precision mediump float;\n"
		""
		"uniform sampler2D uTexture;\n"
		""
		"varying vec2 vTexCoord;\n"
		""
		"void main() {"
		"	gl_FragColor = texture2D(uTexture, vTexCoord);"
		"}";

#define FUNC_POINTER_DEC(ret,func,params) extern ret (KHRONOS_APIENTRY *func) params;
	FUNC_POINTER_DEC(void, glActiveTexture, (GLenum))
	FUNC_POINTER_DEC(void, glAttachShader, (GLuint, GLuint))
	FUNC_POINTER_DEC(void, glBindAttribLocation, (GLuint, GLuint, const GLchar*))
	FUNC_POINTER_DEC(void, glBindBuffer, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glBindFramebuffer, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glBindRenderbuffer, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glBindTexture, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glBlendColor, (GLclampf, GLclampf, GLclampf, GLclampf))
	FUNC_POINTER_DEC(void, glBlendEquation, ( GLenum ))
	FUNC_POINTER_DEC(void, glBlendEquationSeparate, (GLenum, GLenum))
	FUNC_POINTER_DEC(void, glBlendFunc, (GLenum, GLenum))
	FUNC_POINTER_DEC(void, glBlendFuncSeparate, (GLenum, GLenum, GLenum, GLenum))
	FUNC_POINTER_DEC(void, glBufferData, (GLenum, GLsizeiptr, const GLvoid*, GLenum))
	FUNC_POINTER_DEC(void, glBufferSubData, (GLenum, GLintptr, GLsizeiptr, const GLvoid*))
	FUNC_POINTER_DEC(GLenum, glCheckFramebufferStatus, (GLenum))
	FUNC_POINTER_DEC(void, glClear, (GLbitfield))
	FUNC_POINTER_DEC(void, glClearColor, (GLclampf, GLclampf, GLclampf, GLclampf))
	FUNC_POINTER_DEC(void, glClearDepthf, (GLclampf))
	FUNC_POINTER_DEC(void, glClearStencil, (GLint))
	FUNC_POINTER_DEC(void, glColorMask, (GLboolean, GLboolean, GLboolean, GLboolean))
	FUNC_POINTER_DEC(void, glCompileShader, (GLuint))
	FUNC_POINTER_DEC(void, glCompressedTexImage2D, (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*))
	FUNC_POINTER_DEC(void, glCompressedTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*))
	FUNC_POINTER_DEC(void, glCopyTexImage2D, (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint))
	FUNC_POINTER_DEC(void, glCopyTexSubImage2D, (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei))
	FUNC_POINTER_DEC(GLuint, glCreateProgram, (void))
	FUNC_POINTER_DEC(GLuint, glCreateShader, (GLenum))
	FUNC_POINTER_DEC(void, glCullFace, (GLenum))
	FUNC_POINTER_DEC(void, glDeleteBuffers, (GLsizei, const GLuint*))
	FUNC_POINTER_DEC(void, glDeleteFramebuffers, (GLsizei, const GLuint*))
	FUNC_POINTER_DEC(void, glDeleteProgram, (GLuint))
	FUNC_POINTER_DEC(void, glDeleteRenderbuffers, (GLsizei, const GLuint*))
	FUNC_POINTER_DEC(void, glDeleteShader, (GLuint))
	FUNC_POINTER_DEC(void, glDeleteTextures, (GLsizei, const GLuint*))
	FUNC_POINTER_DEC(void, glDepthFunc, (GLenum))
	FUNC_POINTER_DEC(void, glDepthMask, (GLboolean))
	FUNC_POINTER_DEC(void, glDepthRangef, (GLclampf, GLclampf))
	FUNC_POINTER_DEC(void, glDetachShader, (GLuint, GLuint))
	FUNC_POINTER_DEC(void, glDisable, (GLenum))
	FUNC_POINTER_DEC(void, glDisableVertexAttribArray, (GLuint))
	FUNC_POINTER_DEC(void, glDrawArrays, (GLenum, GLint, GLsizei))
	FUNC_POINTER_DEC(void, glDrawElements, (GLenum, GLsizei, GLenum, const GLvoid*))
	FUNC_POINTER_DEC(void, glEnable, (GLenum))
	FUNC_POINTER_DEC(void, glEnableVertexAttribArray, (GLuint))
	FUNC_POINTER_DEC(void, glFinish, (void))
	FUNC_POINTER_DEC(void, glFlush, (void))
	FUNC_POINTER_DEC(void, glFramebufferRenderbuffer, (GLenum, GLenum, GLenum, GLuint))
	FUNC_POINTER_DEC(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint))
	FUNC_POINTER_DEC(void, glFrontFace, (GLenum))
	FUNC_POINTER_DEC(void, glGenBuffers, (GLsizei, GLuint*))
	FUNC_POINTER_DEC(void, glGenerateMipmap, (GLenum))
	FUNC_POINTER_DEC(void, glGenFramebuffers, (GLsizei, GLuint*))
	FUNC_POINTER_DEC(void, glGenRenderbuffers, (GLsizei, GLuint*))
	FUNC_POINTER_DEC(void, glGenTextures, (GLsizei, GLuint*))
	FUNC_POINTER_DEC(void, glGetActiveAttrib, (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*))
	FUNC_POINTER_DEC(void, glGetActiveUniform, (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*))
	FUNC_POINTER_DEC(void, glGetAttachedShaders, (GLuint, GLsizei, GLsizei*, GLuint*))
	FUNC_POINTER_DEC(int, glGetAttribLocation, (GLuint, const GLchar*))
	FUNC_POINTER_DEC(void, glGetBooleanv, (GLenum, GLboolean*))
	FUNC_POINTER_DEC(void, glGetBufferParameteriv, (GLenum, GLenum, GLint*))
	FUNC_POINTER_DEC(GLenum, glGetError, (void))
	FUNC_POINTER_DEC(void, glGetFloatv, (GLenum, GLfloat*))
	FUNC_POINTER_DEC(	void, glGetFramebufferAttachmentParameteriv, (GLenum, GLenum, GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetIntegerv, (GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetProgramiv, (GLuint, GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetProgramInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
	FUNC_POINTER_DEC(void, glGetRenderbufferParameteriv, (GLenum, GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetShaderiv, (GLuint, GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
	FUNC_POINTER_DEC(void, glGetShaderPrecisionFormat, (GLenum, GLenum, GLint*, GLint*))
	FUNC_POINTER_DEC(void, glGetShaderSource, (GLuint, GLsizei, GLsizei*, GLchar*))
	FUNC_POINTER_DEC(const GLubyte*, glGetString, (GLenum))
	FUNC_POINTER_DEC(void, glGetTexParameterfv, (GLenum  GLenum, GLfloat*))
	FUNC_POINTER_DEC(void, glGetTexParameteriv, (GLenum, GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetUniformfv, (GLuint, GLint, GLfloat*))
	FUNC_POINTER_DEC(void, glGetUniformiv, (GLuint, GLint, GLint*))
	FUNC_POINTER_DEC(int, glGetUniformLocation, (GLuint, const GLchar*))
	FUNC_POINTER_DEC(void, glGetVertexAttribfv, (GLuint, GLenum, GLfloat*))
	FUNC_POINTER_DEC(void, glGetVertexAttribiv, (GLuint, GLenum, GLint*))
	FUNC_POINTER_DEC(void, glGetVertexAttribPointerv, (GLuint, GLenum, GLvoid**))
	FUNC_POINTER_DEC(void, glHint, (GLenum, GLenum))
	FUNC_POINTER_DEC(GLboolean, glIsBuffer, (GLuint))
	FUNC_POINTER_DEC(GLboolean, glIsEnabled, (GLenum))
	FUNC_POINTER_DEC(GLboolean, glIsFramebuffer, (GLuint))
	FUNC_POINTER_DEC(GLboolean, glIsProgram, (GLuint))
	FUNC_POINTER_DEC(GLboolean, glIsRenderbuffer, (GLuint))
	FUNC_POINTER_DEC(GLboolean, glIsShader, (GLuint))
	FUNC_POINTER_DEC(GLboolean, glIsTexture, (GLuint))
	FUNC_POINTER_DEC(void, glLineWidth, (GLfloat))
	FUNC_POINTER_DEC(void, glLinkProgram, (GLuint))
	FUNC_POINTER_DEC(void, glPixelStorei, (GLenum, GLint))
	FUNC_POINTER_DEC(void, glPolygonOffset, (GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glReadPixels, (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*))
	FUNC_POINTER_DEC(void, glReleaseShaderCompiler, (void))
	FUNC_POINTER_DEC(void, glRenderbufferStorage, (GLenum, GLenum, GLsizei, GLsizei))
	FUNC_POINTER_DEC(void, glSampleCoverage, (GLclampf, GLboolean))
	FUNC_POINTER_DEC(void, glScissor, (GLint, GLint, GLsizei, GLsizei))
	FUNC_POINTER_DEC(void, glShaderBinary, (GLsizei, const GLuint*, GLenum, const GLvoid*, GLsizei))
	FUNC_POINTER_DEC(void, glShaderSource, (GLuint, GLsizei, const GLchar* const*, const GLint*))
	FUNC_POINTER_DEC(void, glStencilFunc, (GLenum, GLint, GLuint))
	FUNC_POINTER_DEC(void, glStencilFuncSeparate, (GLenum, GLenum, GLint, GLuint))
	FUNC_POINTER_DEC(void, glStencilMask, (GLuint))
	FUNC_POINTER_DEC(void, glStencilMaskSeparate, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glStencilOp, (GLenum, GLenum, GLenum))
	FUNC_POINTER_DEC(void, glStencilOpSeparate, (GLenum, GLenum, GLenum, GLenum))
	FUNC_POINTER_DEC(void, glTexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*))
	FUNC_POINTER_DEC(void, glTexParameterf, (GLenum, GLenum, GLfloat))
	FUNC_POINTER_DEC(void, glTexParameterfv, (GLenum, GLenum, const GLfloat*))
	FUNC_POINTER_DEC(void, glTexParameteri, (GLenum, GLenum, GLint))
	FUNC_POINTER_DEC(void, glTexParameteriv, (GLenum, GLenum, const GLint*))
	FUNC_POINTER_DEC(void, glTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*))
	FUNC_POINTER_DEC(void, glUniform1f, (GLint, GLfloat))
	FUNC_POINTER_DEC(void, glUniform1fv, (GLint, GLsizei, const GLfloat*))
	FUNC_POINTER_DEC(void, glUniform1i, (GLint, GLint))
	FUNC_POINTER_DEC(void, glUniform1iv, (GLint, GLsizei, const GLint*))
	FUNC_POINTER_DEC(void, glUniform2f, (GLint, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glUniform2fv, (GLint, GLsizei, const GLfloat*))
	FUNC_POINTER_DEC(void, glUniform2i, (GLint, GLint, GLint))
	FUNC_POINTER_DEC(void, glUniform2iv, (GLint, GLsizei, const GLint*))
	FUNC_POINTER_DEC(void, glUniform3f, (GLint, GLfloat, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glUniform3fv, (GLint, GLsizei, const GLfloat*))
	FUNC_POINTER_DEC(void, glUniform3i, (GLint, GLint, GLint, GLint))
	FUNC_POINTER_DEC(void, glUniform3iv, (GLint, GLsizei, const GLint*))
	FUNC_POINTER_DEC(void, glUniform4f, (GLint, GLfloat, GLfloat, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glUniform4fv, (GLint, GLsizei, const GLfloat*))
	FUNC_POINTER_DEC(void, glUniform4i, (GLint, GLint, GLint, GLint, GLint))
	FUNC_POINTER_DEC(void, glUniform4iv, (GLint, GLsizei, const GLint*))
	FUNC_POINTER_DEC(void, glUniformMatrix2fv, (GLint, GLsizei, GLboolean, const GLfloat*))
	FUNC_POINTER_DEC(void, glUniformMatrix3fv, (GLint, GLsizei, GLboolean, const GLfloat*))
	FUNC_POINTER_DEC(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat*))
	FUNC_POINTER_DEC(void, glUseProgram, (GLuint))
	FUNC_POINTER_DEC(void, glValidateProgram, (GLuint))
	FUNC_POINTER_DEC(void, glVertexAttrib1f, (GLuint, GLfloat))
	FUNC_POINTER_DEC(void, glVertexAttrib1fv, (GLuint, const GLfloat*))
	FUNC_POINTER_DEC(void, glVertexAttrib2f, (GLuint, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glVertexAttrib2fv, (GLuint, const GLfloat*))
	FUNC_POINTER_DEC(void, glVertexAttrib3f, (GLuint, GLfloat, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glVertexAttrib3fv, (GLuint, const GLfloat*))
	FUNC_POINTER_DEC(void, glVertexAttrib4f, (GLuint, GLfloat, GLfloat, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glVertexAttrib4fv, (GLuint, const GLfloat*))
	FUNC_POINTER_DEC(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*))
	FUNC_POINTER_DEC(void, glViewport, (GLint, GLint, GLsizei, GLsizei))
#undef FuncPointer

	void initGLES2();

#endif // MW_OPENGLES2

} // Namespace mw.

#endif // MW_OPENGL_H
