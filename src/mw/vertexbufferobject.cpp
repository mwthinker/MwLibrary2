#if MW_OPENGLES2
#include "vertexbufferobject.h"
#include "opengl.h"
#include "window.h"

namespace mw {

	VertexBufferObject::VertexBufferObject() : vboId_(0), target_(0), size_(0), data_(std::make_shared<Data>()) {
	}

	void VertexBufferObject::bindBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
		if (vboId_ == 0) {
			target_ = target;
			size_ = size;
			mw::glGenBuffers(1, &vboId_);
			mw::glBindBuffer(target, vboId_);
			mw::glBufferData(target, size, data, usage);
			mw::glBindBuffer(target_, 0);
			data_->vboId_ = vboId_;
			data_->windowInstance_ = Window::getInstanceId();
		}
	}

	void VertexBufferObject::bindBufferSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data) const {
		if (vboId_ != 0) {
			mw::glBindBuffer(target_, vboId_);
			mw::glBufferSubData(target_, offset, size, data);
			mw::glBindBuffer(target_, 0);
		}
	}

	void VertexBufferObject::bindBuffer() const {
		if (vboId_ != 0) {
			mw::glBindBuffer(target_, vboId_);
		}
	}

	void VertexBufferObject::unbindBuffer() const {
		mw::glBindBuffer(target_, 0);
	}

	VertexBufferObject::Data::Data() : 
		vboId_(0),
		windowInstance_(0) {

	}

	VertexBufferObject::Data::~Data() {
		// Opengl buffer loaded? And the opengl context active?
		if (vboId_ != 0 && windowInstance_ == Window::getInstanceId()) {
			// Is called if the buffer is valid and therefore need to be cleaned up.
			mw::glDeleteBuffers(1, &vboId_);
		}
	}

} // Namespace mw.

#endif // MW_OPENGLES2
