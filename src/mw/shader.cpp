#include "shader.h"
#include "opengl.h"
#include "window.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

namespace mw {

	int Shader::currentProgramId = 0;

	namespace {		

		GLuint loadShader(GLuint program, GLenum type, const GLchar* shaderSrc) {
			GLuint shader= glCreateShader(type);
			glShaderSource(shader, 1, &shaderSrc, 0);
			checkGlError();
			glCompileShader(shader);
			checkGlError();
			glAttachShader(program, shader);
			checkGlError();
#if _DEBUG
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1) {
				char message[256]; // A arbitrary value big enough to contain message.
				GLsizei size;
				glGetShaderInfoLog(shader, sizeof(message), &size, message);
				std::string str;
				str.append(message, message + size);
				std::cerr << "\n" << shaderSrc << ", error loading shader: " << str << std::endl;
			}
#endif // _DEBUG
			return shader;
		}

	}

	Shader::Shader() : shaderData_(std::make_shared<ShaderData>()) {
	}

	bool Shader::operator==(const Shader& shader) const {
		return shaderData_ == shader.shaderData_;
	}

	Shader::ShaderData::ShaderData() :
		location_(0),
		programObjectId_(0),
		windowInstance_(0) {

	}

	Shader::ShaderData::~ShaderData() {
		// Opengl program loaded? And the opengl context active?
		if (programObjectId_ != 0 && windowInstance_ == Window::getInstanceId()) {
			// Is called if the program is valid and therefore need to be cleaned up.
			glDeleteProgram(programObjectId_);
			currentProgramId = 0;
		}
	}

	void Shader::bindAttribute(std::string attribute) {
		if (shaderData_->programObjectId_ == 0) {
			shaderData_->attributes_[attribute] = shaderData_->location_;
		}
	}

	int Shader::getAttributeLocation(std::string attribute) const {
		auto it = shaderData_->attributes_.find(attribute);
		if (it != shaderData_->attributes_.end()) {
			return it->second;
		}
		return -1;
	}

	int Shader::getUniformLocation(std::string uniform) const {
		if (shaderData_->programObjectId_ != 0) {
			auto it = shaderData_->uniforms_.find(uniform);

			if (it != shaderData_->uniforms_.end()) {
				return it->second;
			} else {
				int loc = glGetUniformLocation(shaderData_->programObjectId_, uniform.c_str());
				if (loc != -1) {
					shaderData_->uniforms_[uniform] = loc;
				}
				return loc;
			}
		}
		return -1;
	}

	bool Shader::loadAndLinkFromFile(std::string vShaderFile, std::string gShaderFile, std::string fShaderFile) {
		if (shaderData_->programObjectId_ == 0 && shaderData_->programObjectId_ == 0) {
			{
				std::ifstream inFile(vShaderFile);
				std::stringstream stream;
				stream << inFile.rdbuf();
				vShaderFile = stream.str();
			}
			if (!gShaderFile.empty()) {
				std::ifstream inFile(gShaderFile);
				std::stringstream stream;
				stream << inFile.rdbuf();
				fShaderFile = stream.str();
			}
			{
				std::ifstream inFile(fShaderFile);
				std::stringstream stream;
				stream << inFile.rdbuf();
				fShaderFile = stream.str();
			}
			return loadAndLink(vShaderFile, gShaderFile, fShaderFile);
		}
		return false;
	}

	bool Shader::loadAndLinkFromFile(std::string vShaderFile, std::string fShaderFile) {
		return loadAndLinkFromFile(vShaderFile, "", fShaderFile);
	}

	bool Shader::loadAndLink(std::string vShader, std::string gShader, std::string fShader) {
		if (shaderData_->programObjectId_ == 0) {
			shaderData_->programObjectId_ = glCreateProgram();
			shaderData_->windowInstance_ = Window::getInstanceId();
			
			if (shaderData_->programObjectId_ == 0) {
				return false;
			}

			loadShader(shaderData_->programObjectId_, GL_VERTEX_SHADER, vShader.c_str());
			if (!gShader.empty()) {
				loadShader(shaderData_->programObjectId_, GL_GEOMETRY_SHADER, gShader.c_str());
			}
			loadShader(shaderData_->programObjectId_, GL_FRAGMENT_SHADER, fShader.c_str());

			// Bind all attributes.
			for (auto& pair : shaderData_->attributes_) {
				glBindAttribLocation(shaderData_->programObjectId_, shaderData_->location_, pair.first.c_str());
				pair.second = shaderData_->location_++;
			}

			glLinkProgram(shaderData_->programObjectId_);

			GLint linked;
			glGetProgramiv(shaderData_->programObjectId_, GL_LINK_STATUS, &linked);
			if (!linked) {
				GLint infoLen = 0;
				glGetProgramiv(shaderData_->programObjectId_, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					char message[256];
					GLsizei size;
					glGetProgramInfoLog(shaderData_->programObjectId_, sizeof(message), &size, message);
					std::string str;
					str.append(message, message + size);
					std::cerr << "Error linking program: " << str << std::endl;
				}
				glDeleteProgram(shaderData_->programObjectId_);
				return false;
			}

			useProgram();
			return true;
		}
		return false;
	}

	bool Shader::loadAndLink(std::string vShader, std::string fShader) {
		return loadAndLink(vShader, "", fShader);
	}

	void Shader::useProgram() const {
		if (shaderData_->programObjectId_ != 0 && currentProgramId != shaderData_->programObjectId_) {
			glUseProgram(shaderData_->programObjectId_);
			currentProgramId = shaderData_->programObjectId_;
		}
	}

} // Namespace mw.
