#pragma once
#include "entt.hpp"
#include "Trengine/Core/Timestep.h"

namespace Trengine {
	class Entity;

	class Scene {

	public:
		Scene();
		~Scene();

		std::shared_ptr<Entity> createEntity(const std::string& name);

		entt::registry& reg() { return this->registry; }

		void onUpdate(Timestep ts);

		void onViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry registry;
		uint32_t viewportWidth;
		uint32_t viewportHeight;
	};
}