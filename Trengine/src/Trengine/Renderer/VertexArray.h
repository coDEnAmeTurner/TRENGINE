#pragma once
#include <memory>
#include "Trengine/Renderer/Buffer.h"

namespace Trengine {
	class VertexArray {
	public:
		virtual ~VertexArray() {}
		virtual void bind() const = 0;
		virtual void unBind() const = 0;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}
