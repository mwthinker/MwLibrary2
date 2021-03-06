#include "vertexdata.h"

#include "vertexbufferobject.h"

#include <iostream>

namespace mw {

	VertexData::VertexData() : maxVertexes_(0), offsetInBytes_(0), dynamic_(true), addedToBuffer_(false), index_(0) {
	}

	void VertexData::drawMode(GLenum mode) {
		unsigned int vertexes = index_ / vertexSizeInFloat();
		if (maxVertexes_ <= vertexes) {
			vertexes = maxVertexes_;
		}

		if (vbo_.getSize() > 0) {
			bind();
			glDrawArrays(mode, offsetInBytes_ / vertexSizeInBytes(), vertexes);
			checkGlError();
		} else {
			std::cerr << "VertexData failed to draw, no vbo binded, i.e. Buffer::uploadToGraphicCard never called." << std::endl;
		}
	}

	void VertexData::begin() {
		index_ = 0;
	}

	void VertexData::end() {
		if (dynamic_) {
			unsigned int size = vertexSizeInBytes() * maxVertexes_;
			if (vbo_.getSize() > 0 && data_.size() * sizeof(GLfloat) <= size) {
				vbo_.bindBuffer();
				vbo_.bindBufferSubData(offsetInBytes_, data_.size() * sizeof(GLfloat), data_.data());
			}
		} else {
			index_ = data_.size();
			maxVertexes_ = data_.size() / vertexSizeInFloat();
		}
	}

	void VertexData::bindBuffer() const {
		vbo_.bindBuffer();
	}

} // Namespace mw.
