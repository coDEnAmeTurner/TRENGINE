#define TR_MAIN_DEFINED 

#include "EditorLayer.h"
#include "../../vendor/imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Trengine {
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
		Trengine::FramebufferSpecification fbSpec;
		fbSpec.width = 1366;
		fbSpec.height = 768;
		frameBuffer = std::shared_ptr<Trengine::Framebuffer>(Trengine::Framebuffer::create(fbSpec));

		activeScene = std::shared_ptr<Scene>(new Scene());
		sceneHierachyPanel.setContext(activeScene);
	}

	void EditorLayer::onAttach() 
	{

		squareEntity = activeScene->createEntity("Square");
		squareEntity->addComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f });
		TR_CORE_INFO("Square Entity: {0}", squareEntity->getComponent<TagComponent>().tag);
		
		mainCameraEntity = activeScene->createEntity("Main Camera");
		mainCameraEntity->addComponent<CameraComponent>(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		mainCameraEntity->addComponent<NativeScriptComponent>().bind<CameraController>();
	}

	void EditorLayer::onUpdate( Timestep timeStep) {

		Renderer2D::resetStats();

		frameBuffer->bind();
		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::clear();

		activeScene->onUpdate(timeStep);

		Renderer2D::endScene();

		frameBuffer->unBind();

	}

	void EditorLayer::onImGuiRender() {
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
					 Application::getInstance()->Close();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();

		ImGui::Begin("Settings");

		auto stats =  Renderer2D::getStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		viewportFocused = ImGui::IsWindowFocused();
		viewportHovered = ImGui::IsWindowHovered();
		Application::getInstance()->getImGUILayer()->setBlockEvents(!viewportFocused || !viewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		if (viewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			frameBuffer->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			activeScene->onViewportResize(viewportSize.x, viewportSize.y);
		}

		uint32_t textureID = frameBuffer->getColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewportSize.x, viewportSize.y}, {0, 1}, {1, 0});
		ImGui::End();
		ImGui::PopStyleVar();

		sceneHierachyPanel.onImGUIRender();

	}

	void EditorLayer::onEvent( Event& e) {
		mainCameraEntity->getComponent<NativeScriptComponent>().instance->onEvent(e);
	}

}