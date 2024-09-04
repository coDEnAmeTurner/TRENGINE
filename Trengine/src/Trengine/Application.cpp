#include "trpch.h"
#include "Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "../Log.h"
#include "glad/glad.h"

namespace Trengine {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application() {
		window = CREATE_WINDOW;
		//assume window is WindowsWindow, this will be modified in the future
		window->setEventCallback(BIND_EVENT_FN(onEvent));
	};

	Application::~Application() {

	};

	Application* Application::getInstance()
	{
		if (!instance)
			instance = CreateApplication();

		return instance;

	}

	void Application::Run() {

		uint vao;
		glCreateVertexArrays(1, &vao);
		TR_CORE_TRACE("VAO: {0}", vao);

		while (true)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			window->onUpdate();

			for (Layer* layer : layerStack)
				layer->onUpdate();
		}
	}

	void Application::onEvent(Event& e) {
		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->onEvent(e);

			if (e.isHandled()) break;
		}
	}
}