#include "trpch.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3_loader.h"
#include "Trengine/Core/Application.h"
#include "ImGUILayer.h"


void Trengine::ImGUILayer::onAttach()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	Application& app = *Application::getInstance();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().GetNativeWindow());

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

}

void Trengine::ImGUILayer::onDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


void Trengine::ImGUILayer::onImGuiRender() 
{
}

void Trengine::ImGUILayer::onEvent(Event& e) {
	if (blockEvents)
	{
		ImGuiIO& io = ImGui::GetIO();

		bool value = e.isHandled();
		value |= e.isInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		value |= e.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;

		e.setHandled(value);
	}
}

void Trengine::ImGUILayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Trengine::ImGUILayer::end() 
{
	ImGuiIO& io = ImGui::GetIO();
	Application* app = Application::getInstance();
	io.DisplaySize = ImVec2(app->getWindow().getWidth(), app->getWindow().getHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}





