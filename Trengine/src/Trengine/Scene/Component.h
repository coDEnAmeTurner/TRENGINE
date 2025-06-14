#pragma once
#include <glm/glm.hpp>
#include "Camera.h"

namespace Trengine {
	struct TransformComponent {
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const {
			glm::mat4 cal_rotation = glm::rotate(glm::mat4(1.0f), rotation.x, { 1,0,0 })
										* glm::rotate(glm::mat4(1.0f), rotation.y, { 0,1,0 })
										* glm::rotate(glm::mat4(1.0f), rotation.z, { 0,0,1 });

			return glm::translate(glm::mat4(1.0f), Translation)
				* cal_rotation
				*glm::scale(glm::mat4(1.0f),Scale);
		}
	};

	struct TagComponent {
		std::string tag = "";

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) {}

	};
	
	struct SpriteRendererComponent {
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: color(color) {}
	};

	struct CameraComponent {
		SceneCamera camera;

		bool primary = false;
		bool fixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projection)
			: camera(projection) {}
		CameraComponent(const glm::mat4& projection, bool primary)
			: CameraComponent(projection) {
			this->primary = primary;
		}
	};

}