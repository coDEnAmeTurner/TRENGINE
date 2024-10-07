#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Trengine {
	class Camera {
	protected:
		glm::mat4 projection;
	public:
		Camera(const glm::mat4& projection)
			: projection(projection) {}

		const glm::mat4& getProjection() const {
			return projection;
		}
	};

	class SceneCamera : public Camera {
	public:
		SceneCamera(const glm::mat4& proj);

		virtual ~SceneCamera() = default;

		void setOrthographic(float size, float nearClip, float farClip);

		void setOrthographic(float size) { orthographicSize = size; recalculateProjection(); }

		void setViewportSize(uint32_t width, uint32_t height);

		float& getSize() { return orthographicSize; }
		void setSize(float size) { orthographicSize = size; }
		float& getNear() { return orthographicNear; }
		void setNear(float nearr) { orthographicNear = nearr; }
		float& getFar() { return orthographicFar; }
		void setFar(float farr) { orthographicFar = farr; }
		float& getAspectRatio() { return aspectRatio; }
		void setAspectRatio(float aspectRatio) { aspectRatio = aspectRatio; }

	private:
		void recalculateProjection();
	private:
		float orthographicSize = 10.0f;
		float orthographicNear = -1.0f, orthographicFar = 1.0f;

		float aspectRatio = 0.0f;
	};
}