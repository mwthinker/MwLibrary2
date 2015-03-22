#include "vertexbufferobject.h"

#include "window.h"

namespace mw {

	VertexBufferObject::VertexBufferObject() : data_(std::make_shared<Data>()), size_(0), vboId_(0), target_(0) {
	}

	void VertexBufferObject::bindBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
		if (vboId_ == 0) {
			target_ = target;
			size_ = size;
			glGenBuffers(1, &vboId_);
			glBindBuffer(target, vboId_);
			glBufferData(target, size, data, usage);
			glBindBuffer(target_, 0);
			data_->vboId_ = vboId_;
			data_->windowInstance_ = Window::getInstanceId();
		}
	}

	void VertexBufferObject::bindBufferSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data) const {
		if (vboId_ != 0) {
			glBindBuffer(target_, vboId_);
			glBufferSubData(target_, offset, size, data);
			glBindBuffer(target_, 0);
		}
	}

	void VertexBufferObject::bindBuffer() const {
		if (vboId_ != 0) {
			glBindBuffer(target_, vboId_);
		}
	}

	void VertexBufferObject::unbindBuffer() const {
		glBindBuffer(target_, 0);
	}

	VertexBufferObject::Data::Data() : 
		vboId_(0),
		windowInstance_(0) {

	}

	VertexBufferObject::Data::~Data() {
		// Opengl buffer loaded? And the opengl context active?
		if (vboId_ != 0 && windowInstance_ == Window::getInstanceId()) {
			// Is called if the buffer is valid and therefore need to be cleaned up.
			glDeleteBuffers(1, &vboId_);
		}
	}

} // Namespace mw.
