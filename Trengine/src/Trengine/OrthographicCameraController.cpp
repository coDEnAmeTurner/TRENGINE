#include "trpch.h"
#include "OrthographicCameraController.h"
#include "Trengine/Core/Input.h"
#include "Trengine/Core/KeyCodes.h"
#include "Events/EventDispatcher.h"

namespace Trengine {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: camera(-aspectRatio * zoomLevel, aspectRatio* zoomLevel, -zoomLevel, zoomLevel),
		rotation(rotation),
		aspectRatio(aspectRatio)
	{

	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{

		if ( Input::isKeyPressed(TR_KEY_A))
			cameraPosition.x -= cameraTranslationSpeed * ts;

		if ( Input::isKeyPressed(TR_KEY_D))
			cameraPosition.x += cameraTranslationSpeed * ts;

		if ( Input::isKeyPressed(TR_KEY_W))
			cameraPosition.y += cameraTranslationSpeed * ts;

		if ( Input::isKeyPressed(TR_KEY_S))
			cameraPosition.y -= cameraTranslationSpeed * ts;

		if (rotation) 
		{
			if ( Input::isKeyPressed(TR_KEY_Q))
				cameraRotation -= cameraRotationSpeed * ts;

			if ( Input::isKeyPressed(TR_KEY_E))
				cameraRotation += cameraRotationSpeed * ts;

			camera.setRotation(cameraRotation);
		}


		camera.setPosition(cameraPosition);
		
	}

	void OrthographicCameraController::onResize(float width, float height) {
		aspectRatio = width / height;
		camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		EventDispatcher dispatcher(&e);
		dispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
		
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		zoomLevel -= e.GetYOffset() * 0.5f;
		zoomLevel = std::max(zoomLevel, 0.25f);	
		camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return true;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
	{
		onResize((float)e.GetWidth(), (float)e.GetHeight());

		return true;
	}

}
