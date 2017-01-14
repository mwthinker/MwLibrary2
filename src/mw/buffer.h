#ifndef MW_BUFFER_H
#define MW_BUFFER_H

#include <mw/vertexbufferobject.h>

#include <vector>
#include <memory>

namespace mw {

	class VertexData;
	using VertexDataPtr = std::shared_ptr<VertexData>;

	class Buffer {
	public:
		Buffer();

		Buffer(bool staticData);

		void uploadToGraphicCard();

		void addVertexData(const VertexDataPtr& vd);

		inline bool isStaticData() const {
			return staticData_;
		}

		inline bool isDynamicData() const {
			return !staticData_;
		}

		void clearBuffer();

	private:
		bool staticData_;
		mw::VertexBufferObject vbo_;
		std::vector<VertexDataPtr> vertexDataList_;
	};

} // Namespace mw.

#endif // MW_BUFFER_H
