#define TR_MAIN_DEFINED
#include "trpch.h"
#include "SceneHierachyPanel.h"
#include "../../vendor/imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

void Trengine::SceneHierachyPanel::onImGUIRender()
{
	ImGui::Begin("Scene Hierachy");

	auto view = context->reg().view<entt::entity>();
	for (auto entityID : view) {
		Entity entity { entityID, context.get() };
		DrawEntityNode(entity);

	}

	ImGui::Begin("Properties");
	if (selectionContext.getEntityHandle() != entt::null)
		drawComponents(selectionContext);
	ImGui::End();

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		selectionContext = {};

	ImGui::End();
}

void Trengine::SceneHierachyPanel::DrawEntityNode(Entity entity)
{
	auto& tc = entity.getComponent<TagComponent>();
	
	ImGuiTreeNodeFlags flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tc.tag.c_str());
	if (ImGui::IsItemClicked())
	{
		selectionContext = entity;
	}

	if (opened) {

		ImGui::TreePop();
	}
}

void Trengine::SceneHierachyPanel::drawComponents(Entity& entity)
{
	if (entity.hasComponent<TagComponent>())
	{
		auto& tag = entity.getComponent<TagComponent>().tag;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer);
		}
	}

	if (entity.hasComponent<TransformComponent>())
	{
		if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{
			auto& transform = entity.getComponent<TransformComponent>().transform;
			ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

			ImGui::TreePop();
		}

	}

	if (entity.hasComponent<SpriteRendererComponent>())
	{
		if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
		{
			auto& color = entity.getComponent<SpriteRendererComponent>().color;
			ImGui::ColorEdit4("Color", glm::value_ptr(color), 0.1f);

			ImGui::TreePop();
		}

	}

	if (entity.hasComponent<CameraComponent>())
	{
		if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
		{
			SceneCamera& camera = entity.getComponent<CameraComponent>().camera;

			auto& size = camera.getSize();
			auto& nearr = camera.getNear();
			auto& farr = camera.getFar();
			auto& ar = camera.getAspectRatio();

			ImGui::DragFloat("Orthographic Near", &nearr, 0.1f);
			ImGui::DragFloat("Orthographic Far", &farr, 0.1f);
			ImGui::DragFloat("Aspect Ratio", &ar, 0.1f);
			ImGui::DragFloat("Orthographic Size", &size, 0.1f);

			camera.setAspectRatio(ar);
			camera.setNear(nearr);
			camera.setFar(farr);
			camera.setSize(size);

			ImGui::TreePop();
		}

	}
}


