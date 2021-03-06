#ifndef MW_SHADER_H
#define MW_SHADER_H

#include "opengl.h"

#include <memory>
#include <string>
#include <map>

namespace mw {

	class Shader {
	public:
		// Create an empty non linked shader.
		Shader();

		bool operator==(const Shader& shader) const;

		bool operator!=(const Shader& other) const;

		// Bind the attribute to the shader.
		// Must be called before linking the shader in order for the attribute to
		// be available. I.e. before calling loadAndLinkShadersFromFile(...).
		void bindAttribute(std::string attribute);

		// Return the gl memory location for the attribute.
		// Return -1 on error.
		int getAttributeLocation(std::string attribute) const;

		// Return the gl memory location for the uniform.
		// Return -1 on error.
		int getUniformLocation(std::string uniform) const;

		// Load shaders from files. Is safe to call multiple times but only the 
		// first successful is "used. Load and link the vertex shader and the 
		// fragment shader in the created program. Return true if the creation
		// is successful else false.
		bool loadAndLinkFromFile(std::string vShaderFile, std::string fShaderFile);

		bool loadAndLinkFromFile(std::string vShaderFile, std::string gShaderFile, std::string fShaderFile);

		// Load shaders string parameters "vShader" and "fShader". Is safe to 
		// call multiple times but only the first successful is "used. Load and
		// link the vertex shader and the fragment shader in the created program.
		// Return true if the creation is successful else false.
		bool loadAndLink(std::string vShader, std::string fShader);

		bool loadAndLink(std::string vShader, std::string gShader, std::string fShader);

		// Uses the current gl program. I.e. a call to glUseProgram.
		// Does nothing if the program is not loaded.
		void useProgram() const;

		// Return if the shader program is linked.
		bool isLinked() const {
			return shaderData_->programObjectId_ != 0;
		}

	private:
		static int currentProgramId;

		struct ShaderData {
			ShaderData();
			~ShaderData();

			std::map<std::string, int> attributes_;
			std::map<std::string, int> uniforms_;
			
			int location_;
			GLuint programObjectId_;
			int windowInstance_;
		};

		std::shared_ptr<ShaderData> shaderData_;
	};

	inline bool Shader::operator==(const Shader& shader) const {
		return shaderData_ == shader.shaderData_;
	}

	inline bool Shader::operator!=(const Shader& other) const {
		return !(*this == other);
	}

} // Namespace mw.

#endif // MW_SHADER_H
