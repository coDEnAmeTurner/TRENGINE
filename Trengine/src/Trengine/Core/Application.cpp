#include "trpch.h"
#include "Application.h"
#include "Trengine/Platform/Windows/WindowsWindow.h"
#include "Log.h"
#include "glad/glad.h"
#include "Trengine/Renderer/Renderer.h"
#include "Trengine/Renderer/RenderCommand.h"

namespace Trengine {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance;

	bool Application::onWindowCloseEvent(WindowCloseEvent& e)
	{
		glfwSetWindowShouldClose(static_cast<GLFWwindow*>(instance->getWindow().GetNativeWindow()), true);

		return true;
	}

	bool Application::onWindowResized(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			minimized = true;
			return false;
		}

		minimized = false;

		Renderer::onWindowResize(e.GetWidth(), e.GetHeight());

		return true;
	}

	Application::Application() 
	{
		instance = this;

		window = CREATE_WINDOW;
		//assume window is WindowsWindow, this will be modified in the future
		window->setEventCallback(BIND_EVENT_FN(onEvent));

		Renderer::init();

		this->imGuiLayer = new ImGUILayer();
		layerStack.PushOverlay(imGuiLayer);

		
	};

	Application::~Application() {

	};

	Application* Application::getInstance()
	{
		return instance;
	}

	void Application::Run() {

		while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window->GetNativeWindow())))
		{
			float time = (float)glfwGetTime();
			Timestep timeStep = time - lastFrameTime;
			lastFrameTime = time;

			for (Layer* layer : layerStack)
				layer->onUpdate(timeStep);
			
			imGuiLayer->begin();
			for (Layer* layer : layerStack)
				layer->onImGuiRender();
			imGuiLayer->end();

			window->onUpdate();
		}
	}

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(&e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowCloseEvent));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResized));

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->onEvent(e);

			if (e.isHandled()) break;
		}
	}
	
	Window& Application::getWindow()
	{
		return *window;
	}
}