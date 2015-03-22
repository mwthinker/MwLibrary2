#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "opengl.h"

#include <memory>

namespace mw {

	class VertexBufferObject {
	public:
		// Create a empty vertex buffer object.
		VertexBufferObject();

		// Generates an id and bind the buffer data to the graphic card. The buffer is then unbind.
		// Will only bind for the first call to this function.
		void bindBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);

		// Replaces the data in the buffer. First the buffer is binded then unbinded.
		// Will replace data if the buffer exists on the graphic card.
		void bindBufferSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data) const;

		// Bind the current vertex buffer with the initial target.
		void bindBuffer() const;

		// Unbind the current vertex buffer.
		void unbindBuffer() const;

		// Return the size in bytes for the current data.
		inline int getSize() const {
			return size_;
		}

		// Return the target specified.
		inline GLenum getTarget() const {
			return target_;
		}

	private:
		class Data {
		public:
			Data();
			~Data();

			GLuint vboId_;
			char windowInstance_;
		};

		std::shared_ptr<Data> data_;
		int size_;
		GLuint vboId_;
		GLenum target_;
	};

} // Namespace mw.

#endif // VERTEXBUFFEROBJECT_H
