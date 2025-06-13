#include "Trengine.h"

#include "Layer/BoostLayer.h"

namespace Trengine {
	class BoostApp : public Application {
	public:
		BoostApp() {
			layerStack.PushLayer(new BoostLayer());
		}

		~BoostApp() {
		}
	};

	//the client defines CreateApplication
	Application* CreateApplication() {
		return new BoostApp();
	}

}