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

		static void setClearColor(const glm::vec4& color) {
			rendererAPI->setClearColor(color);
		}

		static void clear() {
			rendererAPI->clear();
		}
	};

	inline RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}
