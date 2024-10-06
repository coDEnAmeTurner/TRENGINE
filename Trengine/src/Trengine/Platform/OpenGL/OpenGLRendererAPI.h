#pragma once
#include "Trengine/Renderer/RendererAPI.h"

namespace Trengine {
	class OpenGLRendererAPI : public RendererAPI {
	public:

		// Inherited via RendererAPI
		void setClearColor(const glm::vec4& color) override;
		void clear() override;

		void init() override;
		
		void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

		// Inherited via RendererAPI
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	};
}
