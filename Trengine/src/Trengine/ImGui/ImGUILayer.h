#pragma once
#include "Trengine/Core/Core.h"
#include "Trengine/Core/Layer.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"
#include "../Events/KeyTypedEvent.h"
#include "../Events/ApplicationEvent.h"

namespace Trengine {
	class TR_API ImGUILayer : public Layer {
	private:
		float time = 0.0f;
		bool blockEvents = true;

	public:
		ImGUILayer() {};
		~ImGUILayer() {};

		void onAttach() override;
		void onDetach() override;
		void onImGuiRender() override;
		void onEvent(Event& e) override;

		void begin();
		void end();

		void setBlockEvents(bool value) { this->blockEvents = value; };
		bool getBlockEvents() { return this->blockEvents; };
	};

}