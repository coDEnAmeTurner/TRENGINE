#pragma once
#include "Log.h"
#include "Trengine/Events/ApplicationEvent.h"

#ifdef TR_PLATFORM_WINDOWS

extern Trengine::Application* Trengine::CreateApplication();

int main(int argc, char** argv) {
	Trengine::Log::Init();

	auto app = Trengine::CreateApplication();
	app->Run();
	delete app;

}

#endif // TR_PLATFORM_WINDOWS

