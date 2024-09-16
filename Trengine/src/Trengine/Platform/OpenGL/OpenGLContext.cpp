#include "trpch.h"
#include "OpenGLContext.h"
#include "Log.h"
#include "glad/glad.h"

namespace Trengine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle)
	{
		TR_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TR_CORE_ASSERT(status, "Failed to initialize Glad!");

		TR_CORE_INFO("OpenGL Renderer: {0}", (char*)glGetString(GL_VENDOR));

	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(windowHandle);

	}



}
