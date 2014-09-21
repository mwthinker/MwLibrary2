#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H
#if MW_OPENGLES2

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
		};

		GLuint vboId_;
		GLenum target_;
		int size_;
		std::shared_ptr<Data> data_;
	};

} // Namespace mw.

#endif // MW_OPENGLES2
#endif // VERTEXBUFFEROBJECT_H
