#pragma once
#include "../../trpch.h"
#include "Event.h"

namespace Trengine {
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		Event& event;

	public:
		EventDispatcher(Event& event)
			: event(event) {

		}

		template <typename T>
		bool Dispatch(EventFn<T> func) {
			if (event.GetEventType() == T::GetStaticType()) {
				event.handled = func(*(T*)event);
				return true;
				
			}

			return false;
		}

	};

	std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
