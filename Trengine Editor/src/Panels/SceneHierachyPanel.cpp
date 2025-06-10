#define TR_MAIN_DEFINED
#include "trpch.h"
#include "SceneHierachyPanel.h"
#include "../../vendor/imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "../../vendor/imgui/imgui_internal.h"

void Trengine::SceneHierachyPanel::onImGUIRender()
{
	ImGui::Begin("Scene Hierachy");

	auto view = context->reg().view<entt::entity>();
	for (auto entityID : view) {
		Entity entity { entityID, context.get() };
		DrawEntityNode(entity);

	}

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		selectionContext = {};

	//supposed to be 3rd param: over_items : false
	if (ImGui::BeginPopupContextWindow(0,ImGuiPopupFlags_NoOpenOverItems | 1)) {
		if (ImGui::MenuItem("Create Empty Entity"))
			context->createEntity("Empty Entity");

		ImGui::EndPopup();
	}

	ImGui::End();

	ImGui::Begin("Properties");
	if (selectionContext.getEntityHandle() != entt::null)
	{
		drawComponents(selectionContext);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				selectionContext.addComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				selectionContext.addComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	ImGui::End();
}

void Trengine::SceneHierachyPanel::DrawEntityNode(Entity entity)
{
	auto& tag = entity.getComponent<TagComponent>().tag;
	
	ImGuiTreeNodeFlags flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
	if (ImGui::IsItemClicked())
	{
		selectionContext = entity;
	}

	bool entityDeleted = false;
	//supposed to be 3rd param: over_items : false
	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::MenuItem("Delete Entity"))
			entityDeleted = true;

		ImGui::EndPopup();
	}

	if (opened) {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		/*bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
		if (opened)
			ImGui::TreePop();*/

		ImGui::TreePop();
	}

	if (entityDeleted)
	{
		context->DestroyEntity(entity);
		if (selectionContext == entity)
			selectionContext = {};
	}
}

static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.f) {
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);

	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1 });

	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, .1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f,1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1 });

	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, .1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25, 0.8f,1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1 });
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, .1f);
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
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

	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiButtonFlags_AllowItemOverlap;

	if (entity.hasComponent<TransformComponent>())
	{
		bool open = ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treeNodeFlags, "Transform");

		if (open)
		{
			auto& tc = entity.getComponent<TransformComponent>();
			DrawVec3Control("Translation", tc.Translation);
			glm::vec3 rotation = glm::degrees(tc.Rotation);
			DrawVec3Control("Rotation", rotation);
			tc.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", tc.Scale, 1);

			ImGui::TreePop();
		}

	}

	if (entity.hasComponent<SpriteRendererComponent>())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
		bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), treeNodeFlags, "Sprite Renderer Component");
		ImGui::SameLine(ImGui::GetWindowWidth() - 25);
		if (ImGui::Button("+", ImVec2{20, 20})) {
			ImGui::OpenPopup("Component Settings");
		}
		ImGui::PopStyleVar();

		bool removeComponent = false;
		if (ImGui::BeginPopup("Component Settings")) {
			if (ImGui::MenuItem("Remove Component"))
				removeComponent = true;

			ImGui::EndPopup();
		}

		if (open)
		{
			auto& color = entity.getComponent<SpriteRendererComponent>().color;
			ImGui::ColorEdit4("Color", glm::value_ptr(color), 0.1f);

			ImGui::TreePop();
		}

		if (removeComponent)
			entity.removeComponent<SpriteRendererComponent>();
	}

	if (entity.hasComponent<CameraComponent>())
	{
		if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), treeNodeFlags, "Camera"))
		{
			SceneCamera& camera = entity.getComponent<CameraComponent>().camera;

			auto& size = camera.getSize();
			auto& nearr = camera.getNear();
			auto& farr = camera.getFar();
			auto& ar = camera.getAspectRatio();
			auto& primary = entity.getComponent<CameraComponent>().primary;

			ImGui::Checkbox("Primary?", &primary);
			
			if (primary)
			{
				auto view = context->reg().view<CameraComponent>();
				for(auto look_up_entity : view) {
					if (entity == look_up_entity)
						continue;
					context->reg().get<CameraComponent>(look_up_entity).primary = false;
				}

			}
			
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


