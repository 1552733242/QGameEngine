#include "qgpch.h"
#include "Scene.h"
#include "QGame/Scene/Components.h"
#include "QGame/Renderer/Renderer2D.h"
#include <glm/glm.hpp>

#include "Entity.h"
namespace QGame {

	Scene::Scene()
	{
		
		
	}
	Scene::~Scene()
	{
	}
	
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(),this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Undefined" : name;
		return entity;
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio) {
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}

	}
	void Scene::OnUpdate(Timestep& ts)
	{

		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
				if (!nsc.Instance) {
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity,this };
					nsc.Instance->OnCreate();
				}
				nsc.Instance->OnUpdate(ts);

				});

			
			
		}




		Camera* mainCamera = nullptr;
		glm::mat4 cameratransform ;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view) {
				auto& [transform, camera] = m_Registry.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary) {
					mainCamera = &camera.Camera;
					cameratransform = transform.GetTransform();
					break;
				}
			}
		}
		if (mainCamera) {	
			Renderer2D::BeginScene(*mainCamera, cameratransform);


			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group) {
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuare(transform.GetTransform(), sprite.Color);
			}
			Renderer2D::EndScene();

		}
	}
}