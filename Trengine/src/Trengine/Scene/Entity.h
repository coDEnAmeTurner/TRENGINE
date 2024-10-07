#pragma once
#include "Scene.h"
#include "entt.hpp"

namespace Trengine {
	class Entity {
	private:
		entt::entity entityHandle{ entt::null };
		Scene* scene = nullptr;

	public:
		Entity() {}

		Entity(const Entity& e) 
		{
			this->entityHandle = e.entityHandle;
			this->scene = e.scene;
		}

		Entity(entt::entity handle, Scene* sscene) 
			: entityHandle(handle), scene(sscene)
		{
		}

		template<typename T>
		bool hasComponent()
		{
			return scene->reg().all_of<T>(entityHandle);
		}

		template<typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			TR_CORE_ASSERT(!hasComponent<T>(), "Already has this component!");

			return scene->reg().emplace<T>(entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent() {
			TR_CORE_ASSERT(hasComponent<T>(), "Doesn't have this component!");

			return scene->reg().get<T>(entityHandle);
		}

		template<typename T>
		T& removeComponent() {
			TR_CORE_ASSERT(hasComponent<T>(), "Doesn't have this component!");

			return scene->reg().remove<T>(entityHandle);
		}

		operator uint32_t() const { return (uint32_t)entityHandle; }

		bool operator==(const Entity& other) const
		{
			return entityHandle == other.entityHandle && scene == other.scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		entt::entity getEntityHandle() { return entityHandle; }
	};
}
