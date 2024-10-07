#pragma once
#include "ScriptableEntity.h"

namespace Trengine {
	struct NativeScriptComponent {
		ScriptableEntity* instance = nullptr;

		ScriptableEntity* (*instantiateScript)();
		void (*destroyScript)(NativeScriptComponent*);

		template<typename T>
		void bind()
		{
			instantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
			destroyScript = [](NativeScriptComponent* nsc) {
				delete nsc->instance; 
				nsc->instance = NULL;
				};
		}
	};

}
