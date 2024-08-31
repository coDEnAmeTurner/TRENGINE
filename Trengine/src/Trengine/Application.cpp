#include "trpch.h"
#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "../Log.h"
#include "gl/GL.h"

namespace Trengine {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		window = CREATE_WINDOW();
		//assume window is WindowsWindow, this will be modified in the future
		window->setEventCallback(BIND_EVENT_FN(onEvent));
	};

	Application::~Application() {

	};

	void Application::Run() {

		while (true)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			window->onUpdate();
		}
	}

	void Application::onEvent(Event& e) {
		dispatcher.setEvent(&e);

		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		TR_CORE_TRACE("{0}", e.toString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		this->running = false;
		return true;
	}
}