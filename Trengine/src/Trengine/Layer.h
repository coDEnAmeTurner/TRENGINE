#pragma once

#include <string>
#include "Trengine/Core.h"	
#include "Trengine/Events/Event.h"

namespace Trengine {
	class TR_API Layer {
	protected:
		std::string debugName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate() {};
		virtual void onEvent(Event& event) {}

		const std::string& getName() const { return debugName; }
				

	};
}