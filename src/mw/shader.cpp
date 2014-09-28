#if MW_OPENGLES2
#include "shader.h"
#include "opengl.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

namespace mw {

	GLuint loadShader(GLuint program, GLenum type, const GLchar* shaderSrc) {
		GLuint shader;
		shader = mw::glCreateShader(type);
		mw::glShaderSource(shader, 1, &shaderSrc, NULL);
		mw::glCompileShader(shader);
		mw::glAttachShader(program, shader);
		return shader;
	}

	void loadAndLinkShadersFromFile(GLint programObject, std::string vShader, std::string fShader) {
		{
			std::ifstream inFile(vShader);
			std::stringstream stream;
			stream << inFile.rdbuf();
			vShader = stream.str();
		}
		{
			std::ifstream inFile(fShader);
			std::stringstream stream;
			stream << inFile.rdbuf();
			fShader = stream.str();
		}

		loadShader(programObject, GL_VERTEX_SHADER, vShader.c_str());
		loadShader(programObject, GL_FRAGMENT_SHADER, fShader.c_str());

		mw::glLinkProgram(programObject);

		GLint linked;
		mw::glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
		if (!linked) {
			GLint infoLen = 0;
			mw::glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1) {
				char message[256];
				GLsizei size;
				mw::glGetProgramInfoLog(programObject, sizeof(message), &size, message);
				std::string str;
				str.append(message, message + size);
				std::cerr << "Error linking program: " << str << "\n";
			}
			mw::glDeleteProgram(programObject);
			exit(1);
		}
	}

	Shader::Shader() :
		location_(0),
		programObjectId_(0) {

	}

	Shader::~Shader() {
		glDeleteProgram(programObjectId_);
	}

	void Shader::bindAttribute(std::string attribute) {
		assert(programObjectId_ == 0);
		attributes_[attribute] = location_;
	}

	int Shader::getAttributeLocation(std::string attribute) const {
		auto it = attributes_.find(attribute);
		if (it != attributes_.end()) {
			return it->second;
		}
		return -1;
	}

	int Shader::getUniformLocation(std::string uniform) {
		if (programObjectId_ != 0) {
			unsigned int size = uniforms_.size();

			int& loc = uniforms_[uniform];

			if (uniforms_.size() > size) {
				loc = mw::glGetUniformLocation(programObjectId_, uniform.c_str());
			}
			return loc;
		}
		return -1;
	}

	bool Shader::loadAndLinkFromFile(std::string vShaderFile, std::string fShaderFile) {
		if (programObjectId_ == 0) {
			{
				std::ifstream inFile(vShaderFile);
				std::stringstream stream;
				stream << inFile.rdbuf();
				vShaderFile = stream.str();
			}
			{
				std::ifstream inFile(fShaderFile);
				std::stringstream stream;
				stream << inFile.rdbuf();
				fShaderFile = stream.str();
			}
			return loadAndLink(vShaderFile, fShaderFile);
		}
		return false;
	}

	bool Shader::loadAndLink(std::string vShader, std::string fShader) {
		if (programObjectId_ == 0) {
			programObjectId_ = mw::glCreateProgram();
			if (programObjectId_ == 0) {
				return false;
			}

			loadShader(programObjectId_, GL_VERTEX_SHADER, vShader.c_str());
			loadShader(programObjectId_, GL_FRAGMENT_SHADER, fShader.c_str());

			// Bind all attributes.
			for (auto& pair : attributes_) {
				mw::glBindAttribLocation(programObjectId_, location_, pair.first.c_str());
				pair.second = location_++;
			}

			mw::glLinkProgram(programObjectId_);

			GLint linked;
			mw::glGetProgramiv(programObjectId_, GL_LINK_STATUS, &linked);
			if (!linked) {
				GLint infoLen = 0;
				mw::glGetProgramiv(programObjectId_, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					char message[256];
					GLsizei size;
					mw::glGetProgramInfoLog(programObjectId_, sizeof(message), &size, message);
					std::string str;
					str.append(message, message + size);
					std::cerr << "Error linking program: " << str << "\n";
				}
				mw::glDeleteProgram(programObjectId_);
				return false;
			}

			mw::glUseProgram(programObjectId_);
			return true;
		}
		return false;
	}

	void Shader::glUseProgram() const {
		if (programObjectId_ != 0) {
			mw::glUseProgram(programObjectId_);
		}
	}

	ShaderPtr Shader::defaultShader = nullptr;

	ShaderPtr Shader::getDefaultShader() {
		return defaultShader;
	}

	void Shader::setDefaultShader(const ShaderPtr& shader) {
		defaultShader = shader;
	}

} // Namespace mw.

#endif // MW_OPENGLES2
