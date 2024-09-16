#pragma once
#include <trpch.h>
#include "../../Renderer/Buffer.h"

namespace Trengine {
	class OpenGLVertexBuffer : public VertexBuffer {
	private:
		uint32_t rendererID;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void bind() const;
		virtual void unBind() const;

		// Inherited via VertexBuffer
		void setLayout(const BufferLayout& layout) override;

		BufferLayout& getLayout() override;

	};

	class OpenGLIndexBuffer : public IndexBuffer {
	private:
		uint32_t rendererID;
	public:
		OpenGLIndexBuffer(unsigned int* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void bind() const;
		virtual void unBind() const;
	};
}