#pragma once
#include "../../trpch.h"
#include "KeyEvent.h"

namespace Trengine {
	class TR_API KeyPressedEvent : public KeyEvent {
	private:
		int repeatCount;
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), repeatCount(repeatCount)
		{

		}

		int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	};

}
