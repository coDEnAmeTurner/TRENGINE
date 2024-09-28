#pragma once

#include "Window.h"
#include "Trengine/Events/EventDispatcher.h"
#include "Trengine/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Trengine/ImGui/ImGUILayer.h"


namespace Trengine {
	class TR_API Application {
	private:
		std::unique_ptr<Window> window;
		ImGUILayer* imGuiLayer;
		bool onWindowCloseEvent(WindowCloseEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
		float lastFrameTime = 0.0f;
		bool minimized = false;

	protected:
		static Application* instance;
		bool running = true;
		LayerStack layerStack;

	public:
		Application();

		static Application* getInstance();

		void Run();

		void onEvent(Event& e);

		Window& getWindow();

		virtual ~Application();
	};

	Application* CreateApplication();
	

}