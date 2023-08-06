#pragma once
#include <entt.hpp>
#include "Scene.h"

namespace QGame {

	class Entity {

	public:
		Entity() = default;
		Entity(entt::entity entityHandle,Scene* scene);

		template<typename T,typename... Args>
		T& AddComponent(Args&&... args) {
			GAME_CORE_ASSERT(!HasComponent<T>(), "Entity not have component");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...); ;
		}

		template<typename T>
		T& GetComponent() {
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() {
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}


		template<typename T>
		void RemoveComponent() {
			GAME_CORE_ASSERT(!HasComponent<T>(), "Entity not have component");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};

	
}