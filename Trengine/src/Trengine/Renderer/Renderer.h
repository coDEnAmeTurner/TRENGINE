#pragma once
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Trengine {
	class Renderer {
	public:
		static void beginScene(OrthographicCamera& camera);

		static void endScene();

		static void submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};

	inline Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData();

}
