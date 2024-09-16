#pragma once
#include "Trengine/Renderer/RendererAPI.h"

namespace Trengine {
	class OpenGLRendererAPI : public RendererAPI {
	public:

		// Inherited via RendererAPI
		void setClearColor(const glm::vec4& color) override;
		void clear() override;
		void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
