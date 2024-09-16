#pragma once
#include "../../Window.h"
#include "GLFW/glfw3.h"
#include "../../Renderer/GraphicsContext.h"

namespace Trengine {
	class WindowsWindow : public Window {
	private:
		GLFWwindow* window;
		GraphicsContext* context;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFn eventCallBack;
		};

		WindowData data;
		virtual void init(const WindowProps& props);
		virtual void shutDown();

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		virtual void* GetNativeWindow() const { return window; }

		unsigned int getWidth() const override { return data.width; }
		unsigned int getHeight() const override { return data.height; }

		void onUpdate() override;
		void setEventCallback(const EventCallbackFn& callback) override;
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	};
}