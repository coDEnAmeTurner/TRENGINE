#include "EditorLayer.h"

#include "Trengine.h"

namespace Trengine {
	class EditorApp : public Application {
	public:
		EditorApp() {
			layerStack.PushLayer(new EditorLayer());

		
		}

		~EditorApp() {
		}


	};

	//the client defines CreateApplication
	Application* CreateApplication() {
		return new EditorApp();
	}

}