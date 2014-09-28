#ifndef SHADER_H
#define SHADER_H
#if MW_OPENGLES2

#include "opengl.h"

#include <memory>
#include <string>
#include <map>

namespace mw {

	GLuint loadShader(GLuint program, GLenum type, const GLchar* shaderSrc);

	void loadAndLinkShadersFromFile(GLint programObject, std::string vShader, std::string fShader);

	class Shader;
	typedef std::shared_ptr<Shader> ShaderPtr;

	class Shader {
	public:
		// Create a empty non linked shader.
		Shader();
		~Shader();

		// Bind the attribute to the shader.
		// Must be called before linking the shader in order for the attribute to
		// be available. I.e. before calling loadAndLinkShadersFromFile(...).
		void bindAttribute(std::string attribute);

		// Return the gl memory location for the attribute.
		// Return -1 on error.
		int getAttributeLocation(std::string attribute) const;

		// Return the gl memory location for the uniform.
		// Return -1 on error.
		int getUniformLocation(std::string uniform);

		// Load shaders from files. Is safe to call multiple times but only the 
		// first successful is "used. Load and link the vertex shader and the 
		// fragment shader in the created program. Return true if the creation
		// is successful else false.
		bool loadAndLinkFromFile(std::string vShaderFile, std::string fShaderFile);

		// Load shaders string parameters "vShader" and "fShader". Is safe to 
		// call multiple times but only the first successful is "used. Load and
		// link the vertex shader and the fragment shader in the created program.
		// Return true if the creation is successful else false.
		bool loadAndLink(std::string vShader, std::string fShader);

		// Uses the current gl program. I.e. a call to glUseProgram.
		// Does nothing if the program is not loaded.
		void glUseProgram() const;

		// Get the default shader.
		static ShaderPtr getDefaultShader();

		// Set the default shader.
		static void setDefaultShader(const ShaderPtr& shader);

	private:
		std::map<std::string, int> attributes_;
		std::map<std::string, int> uniforms_;

		int location_;
		GLuint programObjectId_;

		static ShaderPtr defaultShader;
	};

} // Namespace mw.

#endif // MW_OPENGLES2
#endif // SHADER_H
