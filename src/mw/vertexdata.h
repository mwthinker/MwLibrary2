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

		virtual ~VertexData() = default;

		unsigned int getOffsetInBytes() const;

		unsigned int getMaxVertexes() const;

		unsigned int vertexSizeInBytes() const;

		void begin();
		void end();

		bool isDynamic() const;

		template <unsigned int VERTEX_SIZE>
		void addVertex(const std::array<GLfloat, VERTEX_SIZE>& vertex);

		template <unsigned int VERTEX_SIZE>
		void addEmptyVertex();

		template <unsigned int VERTEX_SIZE>
		void addEmptyVertexes(int nbr);

		bool isAddedToBuffer() const;

	protected:
		void drawMode(GLenum mode);

		void nextVertex();

		void updateVertex(unsigned int index, float value);

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

	inline unsigned int VertexData::getOffsetInBytes() const {
		return offsetInBytes_;
	}

	inline unsigned int VertexData::getMaxVertexes() const {
		return maxVertexes_;
	}

	inline unsigned int VertexData::vertexSizeInBytes() const {
		return vertexSizeInFloat() * sizeof(GLfloat);
	}

	inline bool VertexData::isDynamic() const {
		return dynamic_;
	}

	template <unsigned int VERTEX_SIZE>
	void VertexData::addVertex(const std::array<GLfloat, VERTEX_SIZE>& vertex) {
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

	template <unsigned int VERTEX_SIZE>
	void VertexData::addEmptyVertex() {
		// Insert garbage data in order for the vertex buffer to be created.
		std::array<GLfloat, VERTEX_SIZE> vertex;
		addVertex<VERTEX_SIZE>(vertex);
	}

	template <unsigned int VERTEX_SIZE>
	void VertexData::addEmptyVertexes(int nbr) {
		for (int i = 0; i < nbr; ++i) {
			addEmptyVertex<VERTEX_SIZE>();
		}
	}

	inline bool VertexData::isAddedToBuffer() const {
		return addedToBuffer_;
	}

	inline void VertexData::nextVertex() {
		index_ += vertexSizeInFloat();
	}

	inline void VertexData::updateVertex(unsigned int index, float value) {
		data_[index_ + index] = value;
	}

} // Namespace mw.

#endif // MW_VERTEXDATA_H
