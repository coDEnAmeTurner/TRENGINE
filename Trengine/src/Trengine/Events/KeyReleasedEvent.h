#pragma once
#include <sstream>
#include "KeyEvent.h"

namespace Trengine {
	class TR_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{

		}


		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

}
