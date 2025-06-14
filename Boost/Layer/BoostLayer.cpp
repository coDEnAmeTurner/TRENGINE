#include "BoostLayer.h"


using namespace Trengine;

BoostLayer::BoostLayer()
	: Layer("BoostLayer")
{
	auto& window = Application::getInstance()->getWindow();
	createCamera(window.getWidth(), window.getHeight());

	Random::Init();
}

void BoostLayer::onAttach()
{
	level.init();

	ImGuiIO io = ImGui::GetIO();
	font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
}

void BoostLayer::onDetach()
{
}

void BoostLayer::onUpdate(Timestep ts)
{
	time += ts;
	if ((int)(time * 10.0f) % 8 > 4)
		blink = !blink;

	if (level.isGameOver())
		state = GameState::GameOver;

	const auto& playerPos = level.getPlayer().getPosition();
	camera->setPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (state)
	{
	case GameState::Play:
	{
		level.onUpdate(ts);
		break;
	}
	}

	// Render
	RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	RenderCommand::clear();

	Renderer2D::beginSceneSingle(*camera);
	level.onRender();
	Renderer2D::endSceneSingle();
}

void BoostLayer::onImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	// UI?

	switch (state)
	{
	case GameState::Play:
	{
		uint32_t playerScore = level.getPlayer().getScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		break;
	}
	case GameState::MainMenu:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::getInstance()->getWindow().getWidth();
		auto height = Application::getInstance()->getWindow().getHeight();
		pos.x += (unsigned int) width * 0.5f - 300.0f;
		pos.y += 50.0f;
		if (blink)
			ImGui::GetForegroundDrawList()->AddText(font, 120.0f, pos, 0xffffffff, "Click to Play!");
		break;
	}
	case GameState::GameOver:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::getInstance()->getWindow().getWidth();
		auto height = Application::getInstance()->getWindow().getHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		if (blink)
			ImGui::GetForegroundDrawList()->AddText(font, 120.0f, pos, 0xffffffff, "Click to Play!");

		pos.x += 200.0f;
		pos.y += 150.0f;
		uint32_t playerScore = level.getPlayer().getScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
}

void BoostLayer::onEvent(Event& e)
{
	EventDispatcher dispatcher(&e);
	dispatcher.dispatch<WindowResizeEvent>(TR_BIND_EVENT_FN(BoostLayer::onWindowResize));
	dispatcher.dispatch<MouseButtonPressedEvent>(TR_BIND_EVENT_FN(BoostLayer::onMouseButtonPressed));
}

bool BoostLayer::onMouseButtonPressed(MouseButtonPressedEvent& e)
{
	if (state == GameState::GameOver)
		level.reset();

	state = GameState::Play;
	return false;
}

bool BoostLayer::onWindowResize(WindowResizeEvent& e)
{
	createCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void BoostLayer::createCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	camera = std::make_shared<OrthographicCamera>(left, right, bottom, top);
}
