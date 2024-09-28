#pragma once
#include "Trengine/Core/Timestep.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Trengine/Renderer/OrthographicCamera.h"

namespace Trengine {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		const OrthographicCamera& getCamera() const { return camera; }
	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	private:
		float aspectRatio;
		float zoomLevel = 1.0f;
		OrthographicCamera camera;

		bool rotation;

		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
		float cameraRotation = 0.0f;
		float cameraTranslationSpeed = 1.0f, cameraRotationSpeed = 1.0f;
	};

}
