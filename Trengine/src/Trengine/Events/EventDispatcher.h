#pragma once
#include "Event.h"

namespace Trengine {
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		Event* event;

	public:
		EventDispatcher()
			: event(NULL)
		{
		}

		EventDispatcher(Event* event)
			: event(event) {

		}

		void setEvent(Event* event) {
			this->event = event;
		}

		Event* getEvent() {
			return event;
		}

		template <typename T>
		bool dispatch(EventFn<T> func) {
			if (event->getEventType() == T::getStaticType()) {
				event->handled = func(*(T*)event);
				return true;
				
			}

			return false;
		}

	};

	std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.toString();
	}
}
