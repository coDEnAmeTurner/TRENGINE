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

		float lastFrameTime = 0.0f;
		bool minimized = false;

		bool onWindowCloseEvent(WindowCloseEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	protected:
		static Application* instance;

		//Layer is a package of related logic of rendering, event handling, gameplay
		LayerStack layerStack;

		bool running = true;

	public:
		Application();
		virtual ~Application();

		void Run();
		void onEvent(Event& e);
		void Close();

		static Application* getInstance();
		ImGUILayer* getImGUILayer() { return imGuiLayer; }
		Window& getWindow();
	};

	Application* CreateApplication();
}