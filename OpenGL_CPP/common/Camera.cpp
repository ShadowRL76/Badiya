#include "Camera.h"


Camera::Camera(GLFWwindow* window)
{
    cameraSpeed = std::make_unique<float>(0.1f); 
    cameraPos = std::make_unique< glm::vec3>(2.5f, 2.0f, -15.0f); 
    cameraFront = std::make_unique< glm::vec3>(0.0f, 0.0f, 1.0f); 
    cameraUp = std::make_unique< glm::vec3>(0.0f, 1.0f, 0.0f);  
}

void Camera::Controls(GLFWwindow* window) const
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        *cameraPos += *cameraSpeed * *cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        *cameraPos -= *cameraSpeed * *cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        *cameraPos -= glm::normalize(glm::cross(*cameraFront, *cameraUp)) * *cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        *cameraPos += glm::normalize(glm::cross(*cameraFront, *cameraUp)) * *cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos->y += 0.25f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos->y -= 0.25f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraFront->y += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        cameraFront->y -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        CameraReset(window); 
}


void Camera::CameraReset(GLFWwindow* window) const
{
    cameraPos->x = 2.5f, cameraPos->y = 2.0f, cameraPos->z = -15.0f,
    cameraFront->x = 0.0f, cameraFront->y = 0.0f, cameraFront->z = 1.0f,
    cameraUp->x = 0.0f, cameraUp->y = 1.0f, cameraUp->z = 0.0f; 
}


glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}


glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(*cameraPos, *cameraPos + *cameraFront, *cameraUp);
}

Camera camera(GLFWwindow* window)
{
	return Camera(window);
}
