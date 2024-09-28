#pragma once
#include <memory>
#include "Trengine/Renderer/VertexArray.h"
#include "Trengine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Trengine {
	class RenderCommand {
	private:
		static RendererAPI* rendererAPI;
	public:
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			rendererAPI->drawIndexed(vertexArray);
		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
		{
			rendererAPI->drawIndexed(vertexArray, indexCount);
		}

		static void setClearColor(const glm::vec4& color) {
			rendererAPI->setClearColor(color);
		}

		static void clear() {
			rendererAPI->clear();
		}

		static void init() {
			rendererAPI->init();
		}

		static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			rendererAPI->setViewport(x, y, width, height);
		}
	};

	inline RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}
