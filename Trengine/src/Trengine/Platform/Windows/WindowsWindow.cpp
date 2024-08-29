#include "WindowsWindow.h"
#include "../../../Log.h"

namespace Trengine {

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
		}
	}
}