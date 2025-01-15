#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

/**
 * @class Camera
 * @brief Manages the camera's position, orientation, and movement in a 3D scene.
 */
class Camera {
private:
	// Smart pointer to define the camera's movement speed.
	std::unique_ptr<float> m_cameraSpeed{};

	// Smart pointer to represent the direction the camera is facing.
	std::unique_ptr<glm::vec3> m_cameraFront{};

	// Smart pointer to store the "up" direction of the camera.
	std::unique_ptr<glm::vec3> m_cameraUp{};

public:
	// Smart pointer to store the camera's position in 3D space.
	std::unique_ptr<glm::vec3> m_cameraPos;
public:
	/**
	 * @brief Constructor for the Camera class.
	 * Initializes the camera's position, direction, "up" vector, and movement speed.
	 * Sets up a default view and orientation for the camera.
	 */
	Camera();

	/**
	 * @brief Handles camera movement based on user input.
	 * Captures input from the given GLFW window to control the camera's position and orientation.
	 * @param p_window The GLFW window to capture user input.
	 */
	void Controls(GLFWwindow* p_window) const; 

	/**
	 * @brief Gets the view matrix for the camera.
	 * The view matrix transforms world coordinates to camera coordinates.
	 * @return A glm::mat4 representing the view matrix.
	 */
	glm::mat4 GetViewMatrix() const;

	/**
	 * @brief Gets the projection matrix for the camera.
	 * The projection matrix transforms 3D coordinates into 2D screen space.
	 * @return A glm::mat4 representing the projection matrix.
	 */
	glm::mat4 GetProjectionMatrix() const;

	/**
	 * @brief Resets the camera to its default position and orientation.
	 * Useful for returning the camera to its starting state.
	 * @param p_window The GLFW window (used for method calls but not directly in this function).
	 */
	void CameraReset(GLFWwindow* p_window) const;

};
