#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <entt/entt.hpp>
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

class Entity;

class Scene
{
private:
	entt::registry m_Registry;
	friend class Entity;
public:
	Scene();
	~Scene();

	Entity CreateEntity(const std::string& name = std::string());

	void OnUpdate(float deltaTime);

	void OnRender();

    struct TagComponent
    {
        std::string Tag;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string tag)
            : Tag(tag) {
        }

        TagComponent() = default;
    };

    struct TransformComponent {
        glm::vec3 position{ 0.0f };
        glm::vec3 rotation{ 0.0f };
        glm::vec3 scale{ 1.0f };

        glm::mat4 GetMatrix() const {
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
            glm::mat4 rotationMat = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
            glm::mat4 scaling = glm::scale(glm::mat4(1.0f), scale);

            return translation * rotationMat * scaling;
        }
    };

};