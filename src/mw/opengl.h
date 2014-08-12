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

#define FUNC_POINTER_DEC(ret,func,params) extern ret (KHRONOS_APIENTRY *func) params;
	FUNC_POINTER_DEC(void, glActiveTexture, (GLenum))
	FUNC_POINTER_DEC(void, glAttachShader, (GLuint, GLuint))
	FUNC_POINTER_DEC(void, glBindAttribLocation, (GLuint, GLuint, const char *))
	FUNC_POINTER_DEC(void, glBindTexture, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glBlendFunc, (GLenum, GLenum))
	FUNC_POINTER_DEC(void, glBlendFuncSeparate, (GLenum, GLenum, GLenum, GLenum))
	FUNC_POINTER_DEC(void, glClear, (GLbitfield))
	FUNC_POINTER_DEC(void, glClearColor, (GLclampf, GLclampf, GLclampf, GLclampf))
	FUNC_POINTER_DEC(void, glCompileShader, (GLuint))
	FUNC_POINTER_DEC(GLuint, glCreateProgram, (void))
	FUNC_POINTER_DEC(GLuint, glCreateShader, (GLenum))
	FUNC_POINTER_DEC(void, glDeleteProgram, (GLuint))
	FUNC_POINTER_DEC(void, glDeleteShader, (GLuint))
	FUNC_POINTER_DEC(void, glDeleteTextures, (GLsizei, const GLuint *))
	FUNC_POINTER_DEC(void, glDisable, (GLenum))
	FUNC_POINTER_DEC(void, glDisableVertexAttribArray, (GLuint))
	FUNC_POINTER_DEC(void, glDrawArrays, (GLenum, GLint, GLsizei))
	FUNC_POINTER_DEC(void, glEnable, (GLenum))
	FUNC_POINTER_DEC(void, glEnableVertexAttribArray, (GLuint))
	FUNC_POINTER_DEC(void, glFinish, (void))
	FUNC_POINTER_DEC(void, glGenFramebuffers, (GLsizei, GLuint *))
	FUNC_POINTER_DEC(void, glGenTextures, (GLsizei, GLuint *))
	FUNC_POINTER_DEC(void, glGetBooleanv, (GLenum, GLboolean *))
	FUNC_POINTER_DEC(const GLubyte *, glGetString, (GLenum))
	FUNC_POINTER_DEC(GLenum, glGetError, (void))
	FUNC_POINTER_DEC(void, glGetIntegerv, (GLenum, GLint *))
	FUNC_POINTER_DEC(void, glGetProgramiv, (GLuint, GLenum, GLint *))
	FUNC_POINTER_DEC(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei *, char *))
	FUNC_POINTER_DEC(void, glGetShaderiv, (GLuint, GLenum, GLint *))
	FUNC_POINTER_DEC(GLint, glGetUniformLocation, (GLuint, const char *))
	FUNC_POINTER_DEC(void, glLinkProgram, (GLuint))
	FUNC_POINTER_DEC(void, glPixelStorei, (GLenum, GLint))
	FUNC_POINTER_DEC(void, glReadPixels, (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*))
	FUNC_POINTER_DEC(void, glScissor, (GLint, GLint, GLsizei, GLsizei))
	FUNC_POINTER_DEC(void, glShaderBinary, (GLsizei, const GLuint *, GLenum, const void *, GLsizei))
	FUNC_POINTER_DEC(void, glShaderSource, (GLuint, GLsizei, const char **, const GLint *))
	FUNC_POINTER_DEC(void, glTexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *))
	FUNC_POINTER_DEC(void, glTexParameteri, (GLenum, GLenum, GLint))
	FUNC_POINTER_DEC(void, glTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *))
	FUNC_POINTER_DEC(void, glUniform1i, (GLint, GLint))
	FUNC_POINTER_DEC(void, glUniform4f, (GLint, GLfloat, GLfloat, GLfloat, GLfloat))
	FUNC_POINTER_DEC(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat *))
	FUNC_POINTER_DEC(void, glUseProgram, (GLuint))
	FUNC_POINTER_DEC(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))
	FUNC_POINTER_DEC(void, glViewport, (GLint, GLint, GLsizei, GLsizei))
	FUNC_POINTER_DEC(void, glBindFramebuffer, (GLenum, GLuint))
	FUNC_POINTER_DEC(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint))
	FUNC_POINTER_DEC(GLenum, glCheckFramebufferStatus, (GLenum))
	FUNC_POINTER_DEC(void, glDeleteFramebuffers, (GLsizei, const GLuint *))
	FUNC_POINTER_DEC(GLint, glGetAttribLocation, (GLuint, const GLchar *))
#undef FuncPointer

	void initGLES2();

	static std::string shader_ver = ""
		"attribute vec4 a_v4Position;"
		"attribute vec4 a_v4FillColor;"
		"varying vec4 v_v4FillColor;"
		""
		"void main() {"
		"	v_v4FillColor = a_v4FillColor;"
		"	gl_Position = a_v4Position;"
		"}";

	static std::string shader_frag = ""
		"precision mediump float;"
		""
		"varying vec4 v_v4FillColor; "
		""
		"void main() {"
		"	gl_FragColor = v_v4FillColor;"
		"}";

#endif // MW_OPENGLES2

} // Namespace mw.

#endif // MW_OPENGL_H
