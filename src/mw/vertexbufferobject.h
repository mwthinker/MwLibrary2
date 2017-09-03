#ifndef MW_VERTEXBUFFEROBJECT_H
#define MW_VERTEXBUFFEROBJECT_H

#include "opengl.h"

#include <memory>

namespace mw {

	class VertexBufferObject {
	public:
		// Create a empty vertex buffer object.
		VertexBufferObject();
		
		bool operator==(const VertexBufferObject& shader) const;

		// Generates an id and bind the buffer data to the graphic card. The buffer is then unbind.
		// Will only bind for the first call to this function.
		void bindBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);

		// Replaces the data in the buffer. The current buffer is binded.
		// Will replace data if the buffer exists on the graphic card.
		void bindBufferSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data) const;

		// Bind the current vertex buffer with the initial target.
		void bindBuffer() const;

		// Unbind the current vertex buffer.
		void unbindBuffer() const;

		// Return the size in bytes for the current data.
		int getSize() const;

		// Return the target specified.
		GLenum getTarget() const;

		static void setIgnoreCurrentBind(bool activate);
		static bool getIgnoreCurrentBind();

	private:
		static int currentBufferIdBinded;
		static bool ignoreCurrentIdBinded;

		class Data {
		public:
			Data();
			~Data();

			GLuint vboId_;
			int windowInstance_;
			int size_;
			GLenum target_;
		};

		std::shared_ptr<Data> data_;
	};

} // Namespace mw.

#endif // MW_VERTEXBUFFEROBJECT_H
