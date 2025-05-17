#include "Scene.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Entity.h"
#include <glm/gtx/euler_angles.hpp>

Scene::~Scene()
{
}


Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
    tag.Tag = name.empty() ? "Entity" : name;

	return entity;
}

