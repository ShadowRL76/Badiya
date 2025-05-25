#include "pch.h"
#include "CameraController.h"
#include "Camera.h"

namespace Badiya {

	glm::vec3 CameraController::MoveForward(const float speed) const
	{
		return m_camera.m_cameraPos += m_camera.m_cameraFront * speed;
	}

	glm::vec3 CameraController::MoveLeft(const float speed)	const
	{
		return m_camera.m_cameraPos -= normalize(cross(m_camera.m_cameraFront, m_camera.m_cameraUp)) * speed;
	}

	glm::vec3 CameraController::MoveRight(const float speed) const
	{
		return m_camera.m_cameraPos += normalize(cross(m_camera.m_cameraFront, m_camera.m_cameraUp)) * speed;
	}

	glm::vec3 CameraController::MoveBackwards(const float speed) const
	{
		return m_camera.m_cameraPos -= m_camera.m_cameraFront * speed;
	}

	glm::vec3 CameraController::MoveUp(const float Position) const
	{
		m_camera.m_cameraPos.y += Position;
		return m_camera.m_cameraPos;
	}

	glm::vec3 CameraController::MoveDown(const float Position) const
	{
		m_camera.m_cameraPos.y -= Position;
		return m_camera.m_cameraPos;
	}
}