#include "trpch.h"
#include <Trengine.h>
#include "../../vendor/imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class SandBox2D : public Trengine::Layer {
private:
	Trengine::OrthographicCameraController cameraController;
	std::shared_ptr<Trengine::Texture2D> leviTexture;
	std::shared_ptr<Trengine::Texture2D> interiorSpriteSheet;
	std::shared_ptr<Trengine::Texture2D> houseBuilderSpriteSheet;
	std::shared_ptr<Trengine::SubTexture2D> chairTexture;
	
	glm::vec4 uColor;

	const uint32_t mapWidth = 24;
	uint32_t mapHeight;
	const char* mapTiles =
		"BBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBOOOOBBBBBBB"
		"BBBBBBBBBBBBBOOOOBBBBBBB"
		"BBBBBBBBBBBBBOOOOBBBBBBB"
		"BBBBBBBBBBBBBOOOOBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBOOOOBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBBBBBBBBBBBBBBBBB"
		"BBBBBBBBOOOOOOBBBBBBBBBB"
		"BBBBBBBBOOOOOOBBBBBBBBBB"
		"BBBBBBBBOOOOOOBBBBBBBBBB"
		"BBBBBBBBOOOOOOBBBBBBBBBB";

	std::unordered_map<char, std::shared_ptr<Trengine::SubTexture2D>> textureMap;

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
		leviTexture = Trengine::Texture2D::create("assets/textures/transparent_levi_ackerman.png");
		interiorSpriteSheet = Trengine::Texture2D::create("assets/game/Modern tiles_Free/Interiors_free/48x48/Interiors_free_48x48.png");
		houseBuilderSpriteSheet = Trengine::Texture2D::create("assets/game/Modern tiles_Free/Interiors_free/48x48/Room_Builder_free_48x48.png");

		mapHeight = strlen(mapTiles) / mapWidth;

		textureMap['O'] = Trengine::SubTexture2D::CreateFromCoords(houseBuilderSpriteSheet, { 11,12 }, { 48, 48 }, { 1, 1 });
		textureMap['B'] = Trengine::SubTexture2D::CreateFromCoords(houseBuilderSpriteSheet, { 11,16 }, { 48, 48 }, { 1, 1 });

		chairTexture = Trengine::SubTexture2D::CreateFromCoords(interiorSpriteSheet, { 13,26 }, { 48, 48 }, { 1, 2 });
	}

	void onUpdate(Trengine::Timestep timeStep) {
		Trengine::Renderer2D::resetStats();

		SET_TIMER_SCOPE("SandBox2D:onUpdate");

		Trengine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Trengine::RenderCommand::clear();

		{
			SET_TIMER_SCOPE("CameraController:onUpdate");

			cameraController.onUpdate(timeStep);
		}

		Trengine::Renderer2D::beginScene((Trengine::OrthographicCamera&)cameraController.getCamera());

		for (uint32_t y = 0; y < mapHeight; y++) {
			for (uint32_t x = 0; x < mapWidth; x++) {
				char tileType = mapTiles[x + y * mapWidth];

				std::shared_ptr<Trengine::SubTexture2D> texture;

				if (textureMap.find(tileType) != textureMap.end())
					texture = textureMap[tileType];
				else
					texture = chairTexture;

				Trengine::Renderer2D::drawQuadSubTexture({ x - mapWidth / 2.0f, mapHeight - y - mapHeight / 2.0f, 0.5f }, { 1, 1 }, 0, texture);
			}
		}

		Trengine::Renderer2D::endScene();

	}

	void onImGuiRender() {
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		bool dockSpaceOpen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) 
				{ 
					Trengine::Application::getInstance()->Close();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Main Square Color", glm::value_ptr(uColor));

		for (auto& result : profileResults) {
			char label[50];
			strcpy(label, result.name);
			strcat(label, " %.3fms");
			ImGui::Text(label, result.time);
		}
		profileResults.clear();

		auto stats = Trengine::Renderer2D::getStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());

		ImGui::End();

		ImGui::Begin("Viewport");

		uint32_t textureID = leviTexture->getRendererId();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });

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