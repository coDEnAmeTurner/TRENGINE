#include "trpch.h"
#include "glad/glad.h"
#include "WindowsWindow.h"
#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyPressedEvent.h"
#include "../../Events/KeyReleasedEvent.h"
#include "../../Events/MouseEvent.h"
#include "../../../Log.h"

namespace Trengine {

	static bool glfwInitialized = false;

	Window* Window::create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	void WindowsWindow::shutDown() {
		glfwDestroyWindow(window);
	}

	WindowsWindow::~WindowsWindow() {
		shutDown();
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		init(props);
	}

	void WindowsWindow::init(const WindowProps& props) {
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		TR_CORE_INFO("Creating window {0} ({1}, {2])", props.title, props.width, props.height);

		if (!glfwInitialized) {
			int success = glfwInit();
			TR_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(glfwErrorCallback);
			glfwInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, NULL);
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TR_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallBack(event);

			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallBack(event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallBack(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallBack(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallBack(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallBack(event);
			});

	}

	void WindowsWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::setVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vSync = enabled;
	}

	bool WindowsWindow::isVSync() const {
		return data.vSync;
	}

	void WindowsWindow::setEventCallback(const Window::EventCallbackFn& callback) {
		data.eventCallBack = callback;
	}

}