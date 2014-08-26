#if MW_OPENGLES2
#include "programgl.h"
#include "opengl.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <cassert>

namespace mw {

	static GLuint loadShader(GLuint program, GLenum type, const GLchar* shaderSrc) {
		GLuint shader;
		shader = mw::glCreateShader(type);
		mw::glShaderSource(shader, 1, &shaderSrc, NULL);
		mw::glCompileShader(shader);
		mw::glAttachShader(program, shader);
		return shader;
	}

	static void loadAndLinkShadersFromFile(GLint programObject, std::string vShader, std::string fShader) {
		std::ifstream inFile(vShader);
		std::stringstream stream;
		stream << inFile.rdbuf();
		vShader = stream.str();
		stream.str("");
		inFile = std::ifstream(fShader);
		stream << inFile.rdbuf();
		fShader = stream.str();

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

	ProgramGl::ProgramGl() {
		programObject_ = 0;
		location_ = 0;
	}

	void ProgramGl::bindAttribute(std::string attribute) {
		assert(programObject_ == 0);
		attributes_[attribute] = location_;
	}

	int ProgramGl::getAttributeLocation(std::string attribute) {
		auto it = attributes_.find(attribute);
		if (it != attributes_.end()) {
			return it->second;
		}
		return -1;
	}

	int ProgramGl::getUniformLocation(std::string uniform) {
		if (programObject_ != 0) {
			unsigned int size = uniforms_.size();

			int& loc = uniforms_[uniform];

			if (uniforms_.size() > size) {
				loc = mw::glGetUniformLocation(programObject_, uniform.c_str());
			}
			return loc;
		}
		return -1;
	}

	bool ProgramGl::loadAndLinkShadersFromFile(std::string vShaderFile, std::string fShaderFile) {
		if (programObject_ == 0) {
			std::ifstream inFile(vShaderFile);
			std::stringstream stream;
			stream << inFile.rdbuf();
			vShaderFile = stream.str();
			stream.str("");
			inFile = std::ifstream(fShaderFile);
			stream << inFile.rdbuf();
			fShaderFile = stream.str();

			return loadAndLinkShaders(vShaderFile, fShaderFile);
		}
		return false;
	}

	bool ProgramGl::loadAndLinkShaders(std::string vShader, std::string fShader) {
		if (programObject_ == 0) {
			programObject_ = mw::glCreateProgram();
			if (programObject_ == 0) {
				return false;
			}

			loadShader(programObject_, GL_VERTEX_SHADER, vShader.c_str());
			loadShader(programObject_, GL_FRAGMENT_SHADER, fShader.c_str());

			// Bind all attributes.
			for (auto& pair : attributes_) {
				mw::glBindAttribLocation(programObject_, location_, pair.first.c_str());
				pair.second = location_++;
			}

			mw::glLinkProgram(programObject_);

			GLint linked;
			mw::glGetProgramiv(programObject_, GL_LINK_STATUS, &linked);
			if (!linked) {
				GLint infoLen = 0;
				mw::glGetProgramiv(programObject_, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					char message[256];
					GLsizei size;
					mw::glGetProgramInfoLog(programObject_, sizeof(message), &size, message);
					std::string str;
					str.append(message, message + size);
					std::cerr << "Error linking program: " << str << "\n";
				}
				mw::glDeleteProgram(programObject_);
				return false;
			}

			mw::glUseProgram(programObject_);
			return true;
		}
		return false;
	}

	void ProgramGl::use() {
		if (programObject_ != 0) {
			mw::glUseProgram(programObject_);
		}
	}

} // Namespace mw.

#endif // MW_OPENGLES2
