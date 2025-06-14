#pragma once

//#include <Trengine.h>
#include "Trengine/Core/Layer.h"
#include "../Random/Random.h"
#include "../Level/Level.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Trengine/Events/ApplicationEvent.h>
#include <Trengine/Events/MouseEvent.h>
#include <Trengine/Core/Application.h>
#include <Trengine/Renderer/RenderCommand.h>
#include <imgui.h>

namespace Trengine {
	class BoostLayer : public Layer {
	private:
		std::shared_ptr<OrthographicCamera> camera;
		Level level;
		ImFont* font;
		float time = 0.0f;
		bool blink = false;

		enum class GameState
		{
			Play = 0, MainMenu = 1, GameOver = 2
		};

		GameState state = GameState::MainMenu;

		void createCamera(uint32_t width, uint32_t height);
	public:
		BoostLayer();
		virtual ~BoostLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;

		void onUpdate(Timestep ts) override;
		virtual void onImGuiRender() override;
		void onEvent(Event& e) override;
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
	};
}