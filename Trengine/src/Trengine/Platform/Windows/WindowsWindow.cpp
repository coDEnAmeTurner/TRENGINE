#include "WindowsWindow.h"
#include "../../../Log.h"

namespace Trengine {

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

			glfwInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, NULL);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

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
}