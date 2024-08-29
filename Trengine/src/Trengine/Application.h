#pragma once

#include "../trpch.h"
#include "Core.h"
#include "Window.h"

namespace Trengine {
	class TR_API Application {
	private:
		std::unique_ptr<Window> window;
		bool running = true;

	public:
		Application();
		virtual ~Application();

		void Run();

		void onEvent(Event& e);
	};

	//to be defined in client, put it here so that the declaration can be included in the client
	Application* CreateApplication();
}