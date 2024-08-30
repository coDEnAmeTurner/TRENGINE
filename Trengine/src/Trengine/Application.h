#pragma once

#include "Window.h"
#include "Events/EventDispatcher.h"

namespace Trengine {
	class TR_API Application {
	private:
		std::unique_ptr<Window> window;
		bool running = true;
		EventDispatcher dispatcher;


		bool OnWindowClose(WindowCloseEvent& e);
	public:
		Application();
		virtual ~Application();

		void Run();

		void onEvent(Event& e);
	};

	//to be defined in client, put it here so that the declaration can be included in the client
	Application* CreateApplication();
}