#pragma once
#include "../Core.h"
#include "spdlog/spdlog.h"

namespace Trengine {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	class Event {
		friend class EventDispatcher;
	protected:
		bool handled = false;
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		bool isHandled() { return handled; }
		void setHandled(bool handled) { this->handled = handled; }
		virtual std::string toString() const { return getName(); }

		bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}

	};
}