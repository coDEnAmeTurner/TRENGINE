#include "trpch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Trengine/Core/Application.h"

namespace Trengine {
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance()->getWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance()->getWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance()->getWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float) xpos, (float) ypos};
	}

	float WindowsInput::getMouseXImpl()
	{
		auto [x, y] = getMousePositionImpl();

		return x;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePositionImpl();

		return y;
	}

}
