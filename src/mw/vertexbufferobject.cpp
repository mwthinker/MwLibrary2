#if MW_OPENGLES2
#include "vertexbufferobject.h"
#include "opengl.h"

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
		}
	}

	void VertexBufferObject::bindBuffer() {
		if (vboId_ != 0) {
			mw::glBindBuffer(target_, vboId_);
		}
	}

	void VertexBufferObject::unbindBuffer() {
		mw::glBindBuffer(target_, 0);
	}

	VertexBufferObject::Data::Data() : vboId_(0) {
	}

	VertexBufferObject::Data::~Data() {
		mw::glDeleteBuffers(1, &vboId_);
	}

} // Namespace mw.

#endif // MW_OPENGLES2
