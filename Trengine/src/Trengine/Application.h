#pragma once

#include "Window.h"
#include "Events/EventDispatcher.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Trengine {
	class TR_API Application {
	private:
		std::unique_ptr<Window> window;

	protected:
		bool running = true;
		LayerStack layerStack;

	public:
		Application();
		virtual ~Application();

		void Run();

		void onEvent(Event& e);
	};

	//to be defined in client, put it here so that the declaration can be included in the client
	Application* CreateApplication();
}