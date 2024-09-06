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