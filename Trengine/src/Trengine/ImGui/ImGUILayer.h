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

		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleaseEvent(MouseButtonReleasedEvent& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrollEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);
	public:
		ImGUILayer() {};
		~ImGUILayer() {};

		void onAttach() override;
		void onDetach() override {};
		void onUpdate();
		void onEvent(Event& event) override;
	};

}