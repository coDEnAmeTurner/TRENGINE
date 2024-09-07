#pragma once
#include "Core.h"
#include "../Log.h"
#include "Events/Event.h"

namespace Trengine {
	using uint = unsigned int;

	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Trengine", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height) {}
	};

	class TR_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() { }
		virtual void onUpdate() = 0;
		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
		
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
		static void glfwErrorCallback(int error, const char* description) {
			TR_CORE_ERROR("GLFW Error ({0}): {1)", error, description);
		}
	};

}