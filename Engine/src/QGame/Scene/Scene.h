#pragma once

#include <entt.hpp>
#include "QGame/Core/Timestep.h"
namespace QGame {
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());
		void DestoryEntity(Entity entity);
		void OnViewportResize(uint32_t width, uint32_t height);
		void OnUpdate(Timestep& ts);
	private:
		template<typename T>
		void OnComponentAdd(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};


}