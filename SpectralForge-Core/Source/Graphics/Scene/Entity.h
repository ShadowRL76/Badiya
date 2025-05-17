#pragma once

#include "Scene.h"

class Entity
{
private:
	entt::entity m_EntityHandle;
	Scene* m_Scene;

public:
	Entity(entt::entity handle, Scene* scene);

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		ENTT_ASSERT(!HasComponent<T>(), "Entity alr has component!");
		return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		ENTT_ASSERT(HasComponent<T>(), "Entity does not component!");

		return m_Scene->m_Registry.get<T>(m_EntityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		ENTT_ASSERT(HasComponent<T>(), "Entity does not component!");
		m_Scene->m_Registry.remove<T>(m_EntityHandle);
	}

	template<typename T>
	bool HasComponent()
	{
		return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
	}
};