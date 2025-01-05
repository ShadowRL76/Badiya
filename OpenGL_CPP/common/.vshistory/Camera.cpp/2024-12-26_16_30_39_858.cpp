#include "Camera.h"


Camera::Camera()
{
    m_cameraSpeed = std::make_unique<float>(0.1f);
    m_cameraPos = std::make_unique< glm::vec3>(2.5f, 2.0f, -15.0f);
    m_cameraFront = std::make_unique< glm::vec3>(0.0f, 0.0f, 1.0f);
    m_cameraUp = std::make_unique< glm::vec3>(0.0f, 1.0f, 0.0f);
}

void Camera::Controls(GLFWwindow* p_window) const
{
    if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
        *m_cameraPos += *m_cameraSpeed * *m_cameraFront;
    if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
        *m_cameraPos -= *m_cameraSpeed * *m_cameraFront;
    if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
        *m_cameraPos -= glm::normalize(glm::cross(*m_cameraFront, *m_cameraUp)) * *m_cameraSpeed;
    if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
        *m_cameraPos += glm::normalize(glm::cross(*m_cameraFront, *m_cameraUp)) * *m_cameraSpeed;
    if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_cameraPos->y += 0.25f;
    if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_cameraPos->y -= 0.25f;
    if (glfwGetKey(p_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_cameraFront->y += 0.05f;
    if (glfwGetKey(p_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        m_cameraFront->y -= 0.05f;
    if (glfwGetKey(p_window, GLFW_KEY_J) == GLFW_PRESS)
        m_cameraFront->x += 0.05f;
    if (glfwGetKey(p_window, GLFW_KEY_K) == GLFW_PRESS)
        m_cameraFront->x -= 0.05f;
    if (glfwGetKey(p_window, GLFW_KEY_R) == GLFW_PRESS)
        CameraReset(p_window);
}


void Camera::CameraReset(GLFWwindow* p_window) const
{
    m_cameraPos->x = 2.5f, m_cameraPos->y = 2.0f, m_cameraPos->z = -15.0f,
        m_cameraFront->x = 0.0f, m_cameraFront->y = 0.0f, m_cameraFront->z = 1.0f,
        m_cameraUp->x = 0.0f, m_cameraUp->y = 1.0f, m_cameraUp->z = 0.0f;
}


glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}


glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(*m_cameraPos, *m_cameraPos + *m_cameraFront, *m_cameraUp);
}

Camera camera()
{
    return Camera();
}
