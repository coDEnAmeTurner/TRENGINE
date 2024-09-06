#pragma once
#include "../Core.h"
#include "Event.h"

namespace Trengine {
	class TR_API KeyEvent : public Event {
	protected:
		int keyCode;

		KeyEvent(int keycode)
			: keyCode(keycode) {

		}

	public:
		inline int getKeyCode() const {
			return keyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
	};
}