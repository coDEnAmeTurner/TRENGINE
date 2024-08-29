#pragma once

#include "Core.h"

namespace Trengine {
	class TR_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to be defined in client, put it here so that the declaration can be included in the client
	Application* CreateApplication();
}