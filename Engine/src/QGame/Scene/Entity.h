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
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdd<T>(*this,component);
			return component;
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
			GAME_CORE_ASSERT(HasComponent<T>(), "Entity not have component");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }
		bool operator==(const Entity& other)const {
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}
		bool operator!=(const Entity& other)const {
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};

	
}