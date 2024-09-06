#include "trpch.h"
#include <Trengine.h>

class ExampleLayer : public Trengine::Layer {
public: 
	ExampleLayer()
		: Layer("Layer 1") {}

	void onUpdate() override {
		TR_CORE_INFO("ExampleLayer::Update");
	}

	void onEvent(Trengine::Event& e) override {
		std::cout << e.toString() << "\n";
		e.setHandled(true);
	}
};

class Sandbox : public Trengine::Application {
public:
	Sandbox() {
		layerStack.PushLayer(new ExampleLayer());
		layerStack.PushOverlay(new Trengine::ImGUILayer());
	}

	~Sandbox() {
	}
};

//the client defines CreateApplication
Trengine::Application* Trengine::CreateApplication() {
	return new Sandbox();
}