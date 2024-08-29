#pragma once
#include "../Log.h"
#include "Events/ApplicationEvent.h"

#ifdef TR_PLATFORM_WINDOWS

//define this somewhere else, in the client of the engine

extern Trengine::Application* Trengine::CreateApplication(); 

int main(int argc, char** argv) {
	Trengine::Log::Init();
	Trengine::WindowResizeEvent e(1280, 720);
	if (e.IsInCategory(Trengine::EventCategoryApplication)) {
		TR_TRACE(e.ToString());

	}

	if (e.IsInCategory(Trengine::EventCategoryInput)) {
		TR_TRACE(e.ToString());
	}


	auto app = Trengine::CreateApplication();
	app->Run();
	delete app;
}

#endif // TR_PLATFORM_WINDOWS

