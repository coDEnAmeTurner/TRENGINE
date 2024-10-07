#pragma once
#include <Trengine.h>
#include <memory>

namespace Trengine {
	class SceneHierachyPanel {
	private:
		std::shared_ptr<Scene> context;
		Entity selectionContext;
	public:
		SceneHierachyPanel() {}

		SceneHierachyPanel(const std::shared_ptr<Scene> scene)
			: context(scene) {};

		void setContext(const std::shared_ptr<Scene> scene) { this->context = scene; };

		void onImGUIRender();

		void DrawEntityNode(Entity entity);

		void drawComponents(Entity& entity);
	};
}
