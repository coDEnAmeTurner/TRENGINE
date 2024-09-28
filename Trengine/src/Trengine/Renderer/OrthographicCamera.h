#pragma once
#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>

namespace Trengine {
	class OrthographicCamera {
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		float rotation = 0.0f;

		
		void recalculateMatrix();
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& getPosition() const { return position; }
		void setPosition(const glm::vec3& position) { this->position = position; recalculateMatrix(); }

		const glm::vec3& getScale() const { return scale; }
		void setScale(const glm::vec3& scale) { this->scale = scale; recalculateMatrix(); }

		float getRotation() const { return rotation; }
		void setRotation(float rotation) { this->rotation = rotation; recalculateMatrix(); }

		const glm::mat4& getProjection() const { return projectionMatrix; }
		void setProjection(float left, float right, float bottom, float top) { 
			this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); 
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}

		const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return viewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }
	};
}
