#pragma once

#include <string>
#include "Trengine/Core/Core.h"	
#include "Trengine/Events/Event.h"
#include "Trengine/Events/EventDispatcher.h"
#include "Trengine/Core/Timestep.h"

namespace Trengine {
	class TR_API Layer {
	protected:
		std::string debugName;

		EventDispatcher dispatcher;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate(Timestep timeStep) {};
		virtual void onEvent(Event& event) {};
		virtual void onImGuiRender() {};


		const std::string& getName() const { return debugName; }
				

	};
}