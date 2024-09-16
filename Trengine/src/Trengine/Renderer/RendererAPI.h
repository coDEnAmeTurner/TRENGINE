#pragma once
#include <memory>
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Trengine {
	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1
		};
	public:
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API getAPI() { return api; }
	private:
		static API api;
	};

	inline RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;
}
