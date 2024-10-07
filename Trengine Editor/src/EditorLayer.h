#pragma once
#include <Trengine.h>
#include "Panels/SceneHierachyPanel.h"

namespace Trengine {
	class EditorLayer : public Trengine::Layer 
	{
	private:
		
		std::shared_ptr<Trengine::Framebuffer> frameBuffer;

		std::shared_ptr<Scene> activeScene;
		std::shared_ptr<Entity> squareEntity;
		std::shared_ptr<Entity> mainCameraEntity;

		SceneHierachyPanel sceneHierachyPanel;

		glm::vec2 viewportSize;

		bool viewportFocused = false;
		bool viewportHovered = false;

	public:
		EditorLayer();
		void onAttach();
		void onUpdate(Trengine::Timestep timeStep);
		void onImGuiRender();
		void onEvent(Trengine::Event& e);
	};

}