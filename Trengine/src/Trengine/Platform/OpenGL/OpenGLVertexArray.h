#pragma once
#include "Trengine/Renderer/VertexArray.h"

namespace Trengine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		virtual void bind() const override;
		virtual void unBind() const override;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

	private:
		uint32_t rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;


		// Inherited via VertexArray
		const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;

		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override;

	};
}
