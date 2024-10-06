#pragma once;
#include "RendererAPI.h"
#include "OrthographicCamera.h"


namespace Trengine {
	class Shader;

	class Renderer {
	public:
		static void init();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		void submit(const std::shared_ptr<VertexArray>& vertexArray, 
			const std::shared_ptr<Shader>& shader, 
			const glm::mat4& transform);

		static void onWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};

	inline Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData();
}
