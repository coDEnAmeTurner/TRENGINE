#include "trpch.h"
#include <Trengine.h>
#include "../../vendor/imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class SandBox2D : public Trengine::Layer {
private:
	Trengine::OrthographicCameraController cameraController;
	std::shared_ptr<Trengine::Texture2D> texture;
	glm::vec4 uColor;

	struct ProfileResult
	{
		const char* name;
		float time;
	};
	std::vector<ProfileResult> profileResults;
public:
	SandBox2D()
		: Layer("SandBox2D"), uColor({ 0, 0, 1, 1 }), cameraController(16 / 9.0, true)
	{
		texture = Trengine::Texture2D::create("assets/textures/transparent_levi_ackerman.png");
	}


	void onUpdate(Trengine::Timestep timeStep) {
		SET_TIMER_SCOPE("SandBox2D:onUpdate");

		Trengine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Trengine::RenderCommand::clear();

		{
			SET_TIMER_SCOPE("CameraController:onUpdate");

			cameraController.onUpdate(timeStep);
		}

		Trengine::Renderer2D::beginScene((Trengine::OrthographicCamera&)cameraController.getCamera());

		Trengine::Renderer2D::drawQuad(glm::vec3(0.0f), glm::vec2(1, 1), glm::vec4(1, 1, 0, 1));
		Trengine::Renderer2D::drawQuad(glm::vec3(0.5f), glm::vec2(1, 1), texture, 1);

		Trengine::Renderer::endScene();
	}

	void onImGuiRender() {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Main Square Color", glm::value_ptr(uColor));

		for (auto& result : profileResults) {
			char label[50];
			strcpy(label, result.name);
			strcat(label, " %.3fms");
			ImGui::Text(label, result.time);
		}
		profileResults.clear();

		ImGui::End();
	}

	void onEvent(Trengine::Event& e) {
		cameraController.onEvent(e);
	}
};

class Sandbox : public Trengine::Application {
public:
	Sandbox() {
		layerStack.PushLayer(new SandBox2D());
	}

	~Sandbox() {
	}
};

//the client defines CreateApplication
Trengine::Application* Trengine::CreateApplication() {
	return new Sandbox();
}