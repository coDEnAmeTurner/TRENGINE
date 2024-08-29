#include <Trengine.h>

class Sandbox : public Trengine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

//the client defines CreateApplication
Trengine::Application* Trengine::CreateApplication() {
	return new Sandbox();
}