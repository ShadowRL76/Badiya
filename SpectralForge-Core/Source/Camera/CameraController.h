#pragma once

#include "Camera/Camera.h"

class CameraController
{
private:
	 Camera& m_camera;
public:
	float m_cameraSpeed{};
	glm::vec3 m_cameraPos{};
public:
	explicit CameraController(Camera& camera) : m_camera(camera) {}

	[[nodiscard]] glm::vec3 MoveForward(const float speed) const;
	[[nodiscard]] glm::vec3 MoveLeft(const float speed) const ;
	[[nodiscard]] glm::vec3 MoveRight(const float speed) const ;
	[[nodiscard]] glm::vec3 MoveBackwards(const float speed) const;
	[[nodiscard]] glm::vec3 MoveUp(const float Position) const;
	[[nodiscard]] glm::vec3 MoveDown(const float Position) const;

};


