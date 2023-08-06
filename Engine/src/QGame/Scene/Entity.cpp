#include "qgpch.h"
#include "Entity.h"

namespace QGame {
	Entity::Entity(entt::entity entityHandle, Scene* scene)
		:m_EntityHandle(entityHandle), m_Scene(scene)
	{


	}
}