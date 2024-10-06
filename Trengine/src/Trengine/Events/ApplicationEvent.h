#pragma once
#include <sstream>
#include "Trengine/Core/Core.h"
#include "Event.h"

namespace Trengine {
	class TR_API WindowResizeEvent : public Event {
	private:
		unsigned int width, height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height) {}

		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class TR_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}