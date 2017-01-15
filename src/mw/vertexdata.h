#ifndef MW_VERTEXDATA_H
#define MW_VERTEXDATA_H

#include "vertexarrayobject.h"
#include "vertexbufferobject.h"

#include <vector>
#include <array>
#include <cassert>

namespace mw {

	class VertexData;
	using VertexDataPtr = std::shared_ptr<VertexData>;

	class VertexData : public VertexArrayObject {
	public:
		friend class Buffer;

		virtual unsigned int vertexSizeInFloat() const = 0;

		virtual void setVertexAttribPointer() const override = 0;

		virtual void useProgram() const override = 0;

		VertexData();

		inline virtual ~VertexData() {
		}

		inline unsigned int getOffsetInBytes() const {
			return offsetInBytes_;
		}

		inline unsigned int getMaxVertexes() const {
			return maxVertexes_;
		}

		unsigned int vertexSizeInBytes() const {
			return vertexSizeInFloat() * sizeof(GLfloat);
		}

		void begin();
		void end();

		inline bool isDynamic() const {
			return dynamic_;
		}

		template <unsigned int N>
		void addVertex(const std::array<float, N>& vertex) {
			// Vertex size must equal the provided vertex size.
			assert(vertex.size() == vertexSizeInFloat());
			if (dynamic_) {
				if (vbo_.getSize() == 0) {
					if (index_ + vertex.size() <= data_.size()) {
						for (float value : vertex) {
							data_[index_++] = value;
						}
					} else {
						for (float value : vertex) {
							data_.push_back(value);
						}
						index_ += vertexSizeInFloat();
					}
				} else if (index_ + vertexSizeInFloat() <= maxVertexes_ * vertexSizeInFloat()) {
					if (index_ < data_.size()) {
						for (float value : vertex) {
							data_[index_++] = value;
						}
					} else {
						for (float value : vertex) {
							data_.push_back(value);
						}
						index_ += vertexSizeInFloat();
					}
				}
			} else {
				for (float value : vertex) {
					data_.push_back(value);
				}
				index_ += vertexSizeInFloat();
			}
		}

		inline bool isAddedToBuffer() const {
			return addedToBuffer_;
		}

	protected:
		void drawMode(GLenum mode);

		inline void nextVertex() {
			index_ += vertexSizeInFloat();
		}

		inline void updateVertex(unsigned int index, float value) {
			data_[index_ + index] = value;
		}

	private:
		void bindBuffer() const override;

		bool addedToBuffer_;
		bool dynamic_;
		int offsetInBytes_;
		unsigned int maxVertexes_;
		unsigned int index_;

		std::vector<GLfloat> data_;
		mw::VertexBufferObject vbo_;
	};

} // Namespace mw.

#endif // MW_VERTEXDATA_H
