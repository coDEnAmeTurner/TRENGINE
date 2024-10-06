#pragma once
#include "trpch.h"
#include "Trengine/Core/Core.h"
#include "Trengine/Events/KeyEvent.h"

namespace Trengine {
	class TR_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
