#pragma once

#include "ScriptableEntity.h"
#include "Component.h"
#include "Trengine/Core/Input.h"
#include <Trengine/Core/KeyCodes.h>
#include <Trengine/Events/EventDispatcher.h>

namespace Trengine {
	class CameraController : public ScriptableEntity
	{
	private:
		float zoomLevel = 1.0f;

		bool onMouseScrolled(MouseScrolledEvent& e)
		{
			zoomLevel -= e.GetYOffset() * 0.5f;
			zoomLevel = std::max(zoomLevel, 0.25f);
			getComponent<CameraComponent>().camera.setOrthographic(zoomLevel);
			return true;
		}

		bool onWindowResized(WindowResizeEvent& e)
		{
			onResize((float)e.GetWidth(), (float)e.GetHeight());

			return true;
		}
	public:
		void onUpdate(Timestep ts) {
			auto& transform = getComponent<TransformComponent>().transform;
			float speed = 5.0f;

			if (Input::isKeyPressed(TR_KEY_A))
				transform[3][0] -= speed * ts;

			if (Input::isKeyPressed(TR_KEY_D))
				transform[3][0] += speed * ts;

			if (Input::isKeyPressed(TR_KEY_W))
				transform[3][1] += speed * ts;

			if (Input::isKeyPressed(TR_KEY_S))
				transform[3][1] -= speed * ts;
		}

		void onEvent(Event& e) {
			EventDispatcher dispatcher(&e);
			dispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(CameraController::onMouseScrolled));
			dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(CameraController::onWindowResized));
		}


	};

}
