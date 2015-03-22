#include "shader.h"
#include "opengl.h"
#include "window.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

namespace mw {

	namespace {		

		GLuint loadShader(GLuint program, GLenum type, const GLchar* shaderSrc) {
			mw::checkGlError();
			GLuint shader= glCreateShader(type);
			
			glShaderSource(shader, 1, &shaderSrc, NULL);
#if _DEBUG
			mw::checkGlError();
#endif // _DEBUG
			glCompileShader(shader);
#if _DEBUG
			mw::checkGlError();
#endif // _DEBUG
			glAttachShader(program, shader);
#if _DEBUG
			mw::checkGlError();
			GLint infoLen = 0;
			
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1) {
				char message[256];
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

	Shader::Shader() :
		location_(0),
		programObjectId_(0),
		shaderData_(std::make_shared<ShaderData>()) {

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
		}
	}

	void Shader::bindAttribute(std::string attribute) {
		if (programObjectId_ == 0) {
			shaderData_->attributes_[attribute] = location_;
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
		if (programObjectId_ != 0) {
			auto it = shaderData_->uniforms_.find(uniform);

			if (it != shaderData_->uniforms_.end()) {
				return it->second;
			} else {
				int loc = glGetUniformLocation(programObjectId_, uniform.c_str());
				if (loc != -1) {
					shaderData_->uniforms_[uniform] = loc;
				}
				return loc;
			}
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

			programObjectId_ = glCreateProgram();
			shaderData_->programObjectId_ = programObjectId_;
			shaderData_->windowInstance_ = Window::getInstanceId();
			if (programObjectId_ == 0) {
				return false;
			}

			loadShader(programObjectId_, GL_VERTEX_SHADER, vShader.c_str());
			loadShader(programObjectId_, GL_FRAGMENT_SHADER, fShader.c_str());

			// Bind all attributes.
			for (auto& pair : shaderData_->attributes_) {
				glBindAttribLocation(programObjectId_, location_, pair.first.c_str());
				pair.second = location_++;
			}

			glLinkProgram(programObjectId_);

			GLint linked;
			glGetProgramiv(programObjectId_, GL_LINK_STATUS, &linked);
			if (!linked) {
				GLint infoLen = 0;
				glGetProgramiv(programObjectId_, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					char message[256];
					GLsizei size;
					glGetProgramInfoLog(programObjectId_, sizeof(message), &size, message);
					std::string str;
					str.append(message, message + size);
					std::cerr << "Error linking program: " << str << std::endl;
				}
				glDeleteProgram(programObjectId_);
				return false;
			}

			glUseProgram();
			return true;
		}
		return false;
	}

	void Shader::glUseProgram() const {
		if (programObjectId_ != 0) {
			::glUseProgram(programObjectId_);
		}
	}

} // Namespace mw.
