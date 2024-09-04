#pragma once

#include "Window.h"
#include "Events/EventDispatcher.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Trengine {
	class TR_API Application {
	private:
		static Application* instance;
		std::unique_ptr<Window> window;

	protected:
		bool running = true;
		LayerStack layerStack;
		Application();
		virtual ~Application();

	public:
		static Application* getInstance();

		void Run();

		void onEvent(Event& e);
	};

	//to be defined in client, put it here so that the declaration can be included in the client
	Application* CreateApplication();
}