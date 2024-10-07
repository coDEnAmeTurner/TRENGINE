#include "trpch.h"
#include "Scene.h"
#include "Component.h"
#include "Trengine/Renderer/Renderer2D.h"
#include "Trengine/Scene/Entity.h"
#include "NativeScriptComponent.h"

namespace Trengine {
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	std::shared_ptr<Entity> Scene::createEntity(const std::string& name)
	{
		Entity* entity = new Entity(registry.create(), this);
		entity->addComponent<TransformComponent>();
		auto& tag = entity->addComponent<TagComponent>();
		tag.tag = name;

		return std::shared_ptr<Entity>(entity);

	}

	void Scene::onUpdate(Timestep ts)
	{
		//scripts
		{
			registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
				if (!nsc.instance)
				{
					nsc.instance = nsc.instantiateScript();
					nsc.instance->entity = Entity(entity, this);
					nsc.instance->onCreate();
				}

				nsc.instance->onUpdate(ts);
				});
		}

		//camera and render
		{
			Camera* mainCamera = nullptr;
			glm::mat4* cameraTransform = nullptr;

			auto& group = registry.view<TransformComponent, CameraComponent>();
			for (auto& entity : group) {
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.primary) {
					mainCamera = &camera.camera;
					cameraTransform = &transform.transform;
					break;
				}
			}

			if (mainCamera)
			{
				Renderer2D::beginScene(*mainCamera, *cameraTransform);

				auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				for (auto entity : group)
				{
					auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

					Renderer2D::drawQuad(transform, sprite.color);
				}

			}
		}
	}

	void Scene::onViewportResize(uint32_t width, uint32_t height)
	{
		viewportWidth = width;
		viewportHeight = height;

		auto view = registry.view<CameraComponent>();
		for (auto& entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.fixedAspectRatio)
				cameraComponent.camera.setViewportSize(width, height);
		}

	}

}
