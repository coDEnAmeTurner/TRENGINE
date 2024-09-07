#pragma once
#include "Trengine/Core.h"
#include "Trengine/Layer.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"
#include "../Events/KeyTypedEvent.h"
#include "../Events/ApplicationEvent.h"

namespace Trengine {
	class TR_API ImGUILayer : public Layer {
	private:
		float time = 0.0f;

	public:
		ImGUILayer() {};
		~ImGUILayer() {};

		void onAttach() override;
		void onDetach() override;
		void onImGuiRender() override;

		void begin();
		void end();
	};

}