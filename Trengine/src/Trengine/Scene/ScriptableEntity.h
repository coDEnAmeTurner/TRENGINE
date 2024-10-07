#pragma once
#include "Entity.h"
#include "Trengine/Events/Event.h"

namespace Trengine {
	class ScriptableEntity {
	private:
		Entity entity;
		friend class Scene;
	public :
		virtual void onCreate() {}
		virtual void onDestroy() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onResize(float width, float height) {}
		virtual void onEvent(Event& e) {}

		virtual ~ScriptableEntity() {};

		template<typename T>
		T& getComponent() {
			return entity.getComponent<T>();
		}
	};
}