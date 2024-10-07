#pragma once
#include "Log.h"

#ifdef TR_PLATFORM_WINDOWS

#ifndef TR_MAIN_DEFINED 

extern Trengine::Application* Trengine::CreateApplication();

int main(int argc, char** argv) {
	Trengine::Log::Init();

	auto app = Trengine::CreateApplication();
	app->Run();
	delete app;

}


#endif

#endif // TR_PLATFORM_WINDOWS

