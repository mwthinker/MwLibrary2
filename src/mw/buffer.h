#ifndef MW_BUFFER_H
#define MW_BUFFER_H

#include "vertexbufferobject.h"

#include <vector>
#include <memory>

namespace mw {

	class VertexData;
	using VertexDataPtr = std::shared_ptr<VertexData>;

	class Buffer {
	public:
		enum Usage {STATIC, DYNAMIC};

		Buffer(Usage usage);

		void uploadToGraphicCard();

		void addVertexData(const VertexDataPtr& vd);

		bool isStaticData() const {
			return staticData_;
		}

		bool isDynamicData() const {
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
