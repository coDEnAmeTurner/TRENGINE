#pragma once
#include "trpch.h"
#include "Trengine/Core/Core.h"

namespace Trengine {
	class TR_API Input {
	private:
		static Input* instance;
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
	public:
		static bool isKeyPressed(int keycode) { return instance->isKeyPressedImpl(keycode); }
		static bool isMouseButtonPressed(int button) { return instance->isMouseButtonPressedImpl(button); }
		static float getMouseX() { return instance->getMouseXImpl(); }
		static float getMouseY() { return instance->getMouseYImpl(); }

	};
}