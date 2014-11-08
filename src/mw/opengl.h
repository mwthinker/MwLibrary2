#ifndef MW_OPENGL_H
#define MW_OPENGL_H

#include "matrix.h"

#if MW_OPENGLES2
#include <SDL_opengles2.h>
#include <string>
#else // MW_OPENGLES2
#include <SDL_opengl.h>
#endif // MW_OPENGLES2

namespace mw {

// Function checkGlError() prints all opengl errors during debug mode.
#if _DEBUG

	// Print all opengl errors.
	// Call check_gl_error instead if the error checking only should be in debug mode.
	void _checkGlError(const char* file, int line);

#define checkGlError() _checkGlError(__FILE__,__LINE__)
#else // _DEBUG

	inline void _empty() {}

#define checkGlError() _empty()
#endif // _DEBUG

	// Return the translation matrix.
	Matrix44 getTranslateMatrix44(float x, float y, float z = 0);

	// Return the rotation matrix.
	Matrix44 getRotateMatrix44(float angle, float x, float y, float z);

	// Return the scale matrix.
	Matrix44 getScaleMatrix44(float x, float y, float z = 1);

	// Return the ortho projection matrix.
	Matrix44 getOrthoProjectionMatrix44(float left, float right, float bottom, float top, float _near = -1, float _far = 1); // _far and _near called due to macro conflict in Windows.

	// Translate the matrix in the xy-plane.
	void translate2D(mw::Matrix44& matrix, float x, float y);
	
	// Rotate the matrix in the xy-plane.
	void rotate2D(mw::Matrix44& matrix, float angle);

	// Scale the matrix in the xy-plane.
	void scale2D(mw::Matrix44& matrix, float sx, float sy);

	// Defines the 2d orthongonal projection matrix.
	void ortho2D(mw::Matrix44& matrix, float left, float right, float bottom, float top);

#if MW_OPENGLES2

	static const std::string SHADER_A_VEC4_POSITION = "aPosition";
	static const std::string SHADER_A_VEC2_TEXCOORD = "aTexCoord";
	
	static const std::string SHADER_U_MAT4_MODEL = "uModelMatrix";
	static const std::string SHADER_U_MAT4_PROJ = "uProjectionMatrix";
	static const std::string SHADER_U_VEC4_COLOR = "uColor";
	static const std::string SHADER_U_FLOAT_TEXTURE = "uIsTexture";
	
	static const std::string SHADER_VER =
		"#version 100\n"
		""
		"precision mediump float;\n"
		""
		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uProjectionMatrix;\n"
		"uniform float uIsTexture;\n"
		""
		"attribute vec4 aPosition;\n"
		"attribute vec2 aTexCoord;\n"
		""
		"varying vec2 vTexCoord;\n"
		""
		"void main() {"
		"	gl_Position = uProjectionMatrix * uModelMatrix * aPosition;"
		"	if (uIsTexture > 0.5) {"
		"		vTexCoord = aTexCoord;"
		"	}"
		"}";

	static const std::string SHADER_FRAG =
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

#define FUNC_POINTER_DEC(ret,func,params) extern ret (KHRONOS_APIENTRY *func) params;
	FUNC_POINTER_DEC(void, glActiveTexture, (GLenum texture))
	FUNC_POINTER_DEC(void, glAttachShader, (GLuint program, GLuint shader))
	FUNC_POINTER_DEC(void, glBindAttribLocation, (GLuint program, GLuint index, const GLchar* name))
	FUNC_POINTER_DEC(void, glBindBuffer, (GLenum target, GLuint buffer))
	FUNC_POINTER_DEC(void, glBindFramebuffer, (GLenum target, GLuint framebuffer))
	FUNC_POINTER_DEC(void, glBindRenderbuffer, (GLenum target, GLuint renderbuffer))
	FUNC_POINTER_DEC(void, glBindTexture, (GLenum target, GLuint texture))
	FUNC_POINTER_DEC(void, glBlendColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))
	FUNC_POINTER_DEC(void, glBlendEquation, (GLenum mode))
	FUNC_POINTER_DEC(void, glBlendEquationSeparate, (GLenum modeRGB, GLenum modeAlpha))
	FUNC_POINTER_DEC(void, glBlendFunc, (GLenum sfactor, GLenum dfactor))
	FUNC_POINTER_DEC(void, glBlendFuncSeparate, (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha))
	FUNC_POINTER_DEC(void, glBufferData, (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage))
	FUNC_POINTER_DEC(void, glBufferSubData, (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data))
	FUNC_POINTER_DEC(GLenum, glCheckFramebufferStatus, (GLenum target))
	FUNC_POINTER_DEC(void, glClear, (GLbitfield mask))
	FUNC_POINTER_DEC(void, glClearColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))
	FUNC_POINTER_DEC(void, glClearDepthf, (GLclampf depth))
	FUNC_POINTER_DEC(void, glClearStencil, (GLint s))
	FUNC_POINTER_DEC(void, glColorMask, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha))
	FUNC_POINTER_DEC(void, glCompileShader, (GLuint shader))
	FUNC_POINTER_DEC(void, glCompressedTexImage2D, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data))
	FUNC_POINTER_DEC(void, glCompressedTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data))
	FUNC_POINTER_DEC(void, glCopyTexImage2D, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border))
	FUNC_POINTER_DEC(void, glCopyTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height))
	FUNC_POINTER_DEC(GLuint, glCreateProgram, (void))
	FUNC_POINTER_DEC(GLuint, glCreateShader, (GLenum type))
	FUNC_POINTER_DEC(void, glCullFace, (GLenum mode))
	FUNC_POINTER_DEC(void, glDeleteBuffers, (GLsizei n, const GLuint* buffers))
	FUNC_POINTER_DEC(void, glDeleteFramebuffers, (GLsizei n, const GLuint* framebuffers))
	FUNC_POINTER_DEC(void, glDeleteProgram, (GLuint program))
	FUNC_POINTER_DEC(void, glDeleteRenderbuffers, (GLsizei n, const GLuint* renderbuffers))
	FUNC_POINTER_DEC(void, glDeleteShader, (GLuint shader))
	FUNC_POINTER_DEC(void, glDeleteTextures, (GLsizei n, const GLuint* textures))
	FUNC_POINTER_DEC(void, glDepthFunc, (GLenum func))
	FUNC_POINTER_DEC(void, glDepthMask, (GLboolean flag))
	FUNC_POINTER_DEC(void, glDepthRangef, (GLclampf zNear, GLclampf zFar))
	FUNC_POINTER_DEC(void, glDetachShader, (GLuint program, GLuint shader))
	FUNC_POINTER_DEC(void, glDisable, (GLenum cap))
	FUNC_POINTER_DEC(void, glDisableVertexAttribArray, (GLuint index))
	FUNC_POINTER_DEC(void, glDrawArrays, (GLenum mode, GLint first, GLsizei count))
	FUNC_POINTER_DEC(void, glDrawElements, (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices))
	FUNC_POINTER_DEC(void, glEnable, (GLenum cap))
	FUNC_POINTER_DEC(void, glEnableVertexAttribArray, (GLuint index))
	FUNC_POINTER_DEC(void, glFinish, (void))
	FUNC_POINTER_DEC(void, glFlush, (void))
	FUNC_POINTER_DEC(void, glFramebufferRenderbuffer, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer))
	FUNC_POINTER_DEC(void, glFramebufferTexture2D, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))
	FUNC_POINTER_DEC(void, glFrontFace, (GLenum mode))
	FUNC_POINTER_DEC(void, glGenBuffers, (GLsizei n, GLuint* buffers))
	FUNC_POINTER_DEC(void, glGenerateMipmap, (GLenum target))
	FUNC_POINTER_DEC(void, glGenFramebuffers, (GLsizei n, GLuint* framebuffers))
	FUNC_POINTER_DEC(void, glGenRenderbuffers, (GLsizei n, GLuint* renderbuffers))
	FUNC_POINTER_DEC(void, glGenTextures, (GLsizei n, GLuint* textures))
	FUNC_POINTER_DEC(void, glGetActiveAttrib, (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name))
	FUNC_POINTER_DEC(void, glGetActiveUniform, (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name))
	FUNC_POINTER_DEC(void, glGetAttachedShaders, (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders))
	FUNC_POINTER_DEC(int, glGetAttribLocation, (GLuint program, const GLchar* name))
	FUNC_POINTER_DEC(void, glGetBooleanv, (GLenum pname, GLboolean* params))
	FUNC_POINTER_DEC(void, glGetBufferParameteriv, (GLenum target, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(GLenum, glGetError, (void))
	FUNC_POINTER_DEC(void, glGetFloatv, (GLenum pname, GLfloat* params))
	FUNC_POINTER_DEC(void, glGetFramebufferAttachmentParameteriv, (GLenum target, GLenum attachment, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetIntegerv, (GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetProgramiv, (GLuint program, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetProgramInfoLog, (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog))
	FUNC_POINTER_DEC(void, glGetRenderbufferParameteriv, (GLenum target, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetShaderiv, (GLuint shader, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetShaderInfoLog, (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog))
	FUNC_POINTER_DEC(void, glGetShaderPrecisionFormat, (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision))
	FUNC_POINTER_DEC(void, glGetShaderSource, (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source))
	FUNC_POINTER_DEC(const GLubyte*, glGetString, (GLenum name))
	FUNC_POINTER_DEC(void, glGetTexParameterfv, (GLenum target, GLenum pname, GLfloat* params))
	FUNC_POINTER_DEC(void, glGetTexParameteriv, (GLenum target, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetUniformfv, (GLuint program, GLint location, GLfloat* params))
	FUNC_POINTER_DEC(void, glGetUniformiv, (GLuint program, GLint location, GLint* params))
	FUNC_POINTER_DEC(int, glGetUniformLocation, (GLuint program, const GLchar* name))
	FUNC_POINTER_DEC(void, glGetVertexAttribfv, (GLuint index, GLenum pname, GLfloat* params))
	FUNC_POINTER_DEC(void, glGetVertexAttribiv, (GLuint index, GLenum pname, GLint* params))
	FUNC_POINTER_DEC(void, glGetVertexAttribPointerv, (GLuint index, GLenum pname, GLvoid** pointer))
	FUNC_POINTER_DEC(void, glHint, (GLenum target, GLenum mode))
	FUNC_POINTER_DEC(GLboolean, glIsBuffer, (GLuint buffer))
	FUNC_POINTER_DEC(GLboolean, glIsEnabled, (GLenum cap))
	FUNC_POINTER_DEC(GLboolean, glIsFramebuffer, (GLuint framebuffer))
	FUNC_POINTER_DEC(GLboolean, glIsProgram, (GLuint program))
	FUNC_POINTER_DEC(GLboolean, glIsRenderbuffer, (GLuint renderbuffer))
	FUNC_POINTER_DEC(GLboolean, glIsShader, (GLuint shader))
	FUNC_POINTER_DEC(GLboolean, glIsTexture, (GLuint texture))
	FUNC_POINTER_DEC(void, glLineWidth, (GLfloat width))
	FUNC_POINTER_DEC(void, glLinkProgram, (GLuint program))
	FUNC_POINTER_DEC(void, glPixelStorei, (GLenum pname, GLint param))
	FUNC_POINTER_DEC(void, glPolygonOffset, (GLfloat factor, GLfloat units))
	FUNC_POINTER_DEC(void, glReadPixels, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels))
	FUNC_POINTER_DEC(void, glReleaseShaderCompiler, (void))
	FUNC_POINTER_DEC(void, glRenderbufferStorage, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height))
	FUNC_POINTER_DEC(void, glSampleCoverage, (GLclampf value, GLboolean invert))
	FUNC_POINTER_DEC(void, glScissor, (GLint x, GLint y, GLsizei width, GLsizei height))
	FUNC_POINTER_DEC(void, glShaderBinary, (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length))
	FUNC_POINTER_DEC(void, glShaderSource, (GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length))
	FUNC_POINTER_DEC(void, glStencilFunc, (GLenum func, GLint ref, GLuint mask))
	FUNC_POINTER_DEC(void, glStencilFuncSeparate, (GLenum face, GLenum func, GLint ref, GLuint mask))
	FUNC_POINTER_DEC(void, glStencilMask, (GLuint mask))
	FUNC_POINTER_DEC(void, glStencilMaskSeparate, (GLenum face, GLuint mask))
	FUNC_POINTER_DEC(void, glStencilOp, (GLenum fail, GLenum zfail, GLenum zpass))
	FUNC_POINTER_DEC(void, glStencilOpSeparate, (GLenum face, GLenum fail, GLenum zfail, GLenum zpass))
	FUNC_POINTER_DEC(void, glTexImage2D, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels))
	FUNC_POINTER_DEC(void, glTexParameterf, (GLenum target, GLenum pname, GLfloat param))
	FUNC_POINTER_DEC(void, glTexParameterfv, (GLenum target, GLenum pname, const GLfloat* params))
	FUNC_POINTER_DEC(void, glTexParameteri, (GLenum target, GLenum pname, GLint param))
	FUNC_POINTER_DEC(void, glTexParameteriv, (GLenum target, GLenum pname, const GLint* params))
	FUNC_POINTER_DEC(void, glTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels))
	FUNC_POINTER_DEC(void, glUniform1f, (GLint location, GLfloat x))
	FUNC_POINTER_DEC(void, glUniform1fv, (GLint location, GLsizei count, const GLfloat* v))
	FUNC_POINTER_DEC(void, glUniform1i, (GLint location, GLint x))
	FUNC_POINTER_DEC(void, glUniform1iv, (GLint location, GLsizei count, const GLint* v))
	FUNC_POINTER_DEC(void, glUniform2f, (GLint location, GLfloat x, GLfloat y))
	FUNC_POINTER_DEC(void, glUniform2fv, (GLint location, GLsizei count, const GLfloat* v))
	FUNC_POINTER_DEC(void, glUniform2i, (GLint location, GLint x, GLint y))
	FUNC_POINTER_DEC(void, glUniform2iv, (GLint location, GLsizei count, const GLint* v))
	FUNC_POINTER_DEC(void, glUniform3f, (GLint location, GLfloat x, GLfloat y, GLfloat z))
	FUNC_POINTER_DEC(void, glUniform3fv, (GLint location, GLsizei count, const GLfloat* v))
	FUNC_POINTER_DEC(void, glUniform3i, (GLint location, GLint x, GLint y, GLint z))
	FUNC_POINTER_DEC(void, glUniform3iv, (GLint location, GLsizei count, const GLint* v))
	FUNC_POINTER_DEC(void, glUniform4f, (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
	FUNC_POINTER_DEC(void, glUniform4fv, (GLint location, GLsizei count, const GLfloat* v))
	FUNC_POINTER_DEC(void, glUniform4i, (GLint location, GLint x, GLint y, GLint z, GLint w))
	FUNC_POINTER_DEC(void, glUniform4iv, (GLint location, GLsizei count, const GLint* v))
	FUNC_POINTER_DEC(void, glUniformMatrix2fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
	FUNC_POINTER_DEC(void, glUniformMatrix3fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
	FUNC_POINTER_DEC(void, glUniformMatrix4fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value))
	FUNC_POINTER_DEC(void, glUseProgram, (GLuint program))
	FUNC_POINTER_DEC(void, glValidateProgram, (GLuint program))
	FUNC_POINTER_DEC(void, glVertexAttrib1f, (GLuint indx, GLfloat x))
	FUNC_POINTER_DEC(void, glVertexAttrib1fv, (GLuint indx, const GLfloat* values))
	FUNC_POINTER_DEC(void, glVertexAttrib2f, (GLuint indx, GLfloat x, GLfloat y))
	FUNC_POINTER_DEC(void, glVertexAttrib2fv, (GLuint indx, const GLfloat* values))
	FUNC_POINTER_DEC(void, glVertexAttrib3f, (GLuint indx, GLfloat x, GLfloat y, GLfloat z))
	FUNC_POINTER_DEC(void, glVertexAttrib3fv, (GLuint indx, const GLfloat* values))
	FUNC_POINTER_DEC(void, glVertexAttrib4f, (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w))
	FUNC_POINTER_DEC(void, glVertexAttrib4fv, (GLuint indx, const GLfloat* values))
	FUNC_POINTER_DEC(void, glVertexAttribPointer, (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr))
	FUNC_POINTER_DEC(void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height))
#undef FuncPointer

	void initGLES2();

#endif // MW_OPENGLES2

} // Namespace mw.

#endif // MW_OPENGL_H
