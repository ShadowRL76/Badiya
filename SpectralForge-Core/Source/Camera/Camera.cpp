#include "pch.h"
#include "Camera.h"

#include "GLFW/glfw3.h"

#include "CameraController.h"

namespace Badiya {
	Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const float speed)
		: m_cameraPos(position),
		m_cameraFront(front),
		m_cameraUp(up),
		m_cameraSpeed(speed)
	{
	}

	void Camera::Controls(GLFWwindow* p_window)
	{
		const CameraController controller(*this);

		if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
			(void)controller.MoveForward(m_cameraSpeed);

		if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
			(void)controller.MoveBackwards(m_cameraSpeed);

		if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
			(void)controller.MoveLeft(m_cameraSpeed);

		if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
			(void)controller.MoveRight(m_cameraSpeed);


		if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			(void)controller.MoveUp(0.25f);

		if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			(void)controller.MoveDown(0.25f);

		if (glfwGetKey(p_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			m_cameraFront.y += 0.05f;
		if (glfwGetKey(p_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
			m_cameraFront.y -= 0.05f;

		if (glfwGetKey(p_window, GLFW_KEY_R) == GLFW_PRESS)
			CameraReset(p_window);
	}


	void Camera::CameraReset(GLFWwindow* p_window)
	{
		m_cameraPos.x = 2.5f; m_cameraPos.y = 2.0f; m_cameraPos.z = -15.0f;
		m_cameraFront.x = 0.0f; m_cameraFront.y = 0.0f; m_cameraFront.z = 1.0f;
		m_cameraUp.x = 0.0f; m_cameraUp.y = 1.0f; m_cameraUp.z = 0.0f;
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	}
}