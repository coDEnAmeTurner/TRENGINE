#pragma once
#include "Trengine/Core/Core.h"
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

		//this allows this to happen: bool Event::IsInCategory(EventCategory category) {
		//return GetCategoryFlags() & category;} and 
		// IsInCategory(EventCategoryInput) returns true if the event belongs to that category.
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
	};
}