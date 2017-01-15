#ifndef MW_VERTEXARRAYOBJECT_H
#define MW_VERTEXARRAYOBJECT_H

#include "opengl.h"

#include <memory>

namespace mw {

	class VertexArrayObject {
	public:
		VertexArrayObject();

		virtual ~VertexArrayObject();

		void bind() const;

		void unbind() const;

		virtual void useProgram() const = 0;

	private:
		virtual void setVertexAttribPointer() const = 0;
		virtual void bindBuffer() const = 0;

		static GLuint currentVertexArrayObject;

		std::shared_ptr<GLuint> vao_;
	};

} // Namespace mw.

#endif // MW_VERTEXARRAYOBJECT_H
