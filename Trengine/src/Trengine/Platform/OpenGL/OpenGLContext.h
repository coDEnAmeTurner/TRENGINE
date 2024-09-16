#pragma once
#include "../../Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Trengine {
	class OpenGLContext : public GraphicsContext {
	private:
		GLFWwindow* windowHandle;
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	};
}
