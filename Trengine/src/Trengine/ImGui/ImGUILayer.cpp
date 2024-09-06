#include "trpch.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "Trengine/Application.h"
#include "ImGUILayer.h"


void Trengine::ImGUILayer::onAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 410");



}

void Trengine::ImGUILayer::onUpdate() {
	ImGuiIO& io = ImGui::GetIO();
	Application* app = Application::getInstance();
	io.DisplaySize = ImVec2(app->getWindow().getWidth(), app->getWindow().getHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = this->time > 0.0f ? (time - this->time) : (1.0f / 60.0f);
	this->time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Trengine::ImGUILayer::onEvent(Event& event)
{
	dispatcher.setEvent(&event);

	dispatcher.dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onMouseButtonPressedEvent));
	dispatcher.dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onMouseButtonReleaseEvent));
	dispatcher.dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onMouseMovedEvent));
	dispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onMouseScrollEvent));
	dispatcher.dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onKeyPressedEvent));
	dispatcher.dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onKeyReleasedEvent));
	dispatcher.dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onKeyTypedEvent));
	dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGUILayer::onWindowResizeEvent));
	
}

bool Trengine::ImGUILayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = true;

	return true;
}

bool Trengine::ImGUILayer::onMouseButtonReleaseEvent(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;

	return true;
}

bool Trengine::ImGUILayer::onMouseMovedEvent(MouseMovedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(e.GetX(), e.GetY());

	return true;
}

bool Trengine::ImGUILayer::onMouseScrollEvent(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += e.GetXOffset();
	io.MouseWheel += e.GetYOffset();

	return true;
}

bool Trengine::ImGUILayer::onKeyPressedEvent(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.getKeyCode()] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return true;
}

bool Trengine::ImGUILayer::onKeyReleasedEvent(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.getKeyCode()] = false;

	return false;
}

bool Trengine::ImGUILayer::onKeyTypedEvent(KeyTypedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	int keycode = e.getKeyCode();
	if (keycode > 0 && keycode < 0x10000)
		io.AddInputCharacter((unsigned short)keycode);

	return true;
}

bool Trengine::ImGUILayer::onWindowResizeEvent(WindowResizeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	glViewport(0, 0, e.GetWidth(), e.GetHeight());

	return true;
}


