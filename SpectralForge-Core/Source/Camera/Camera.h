#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Badiya {
	/**
	 * @class Camera
	 * @brief Manages the camera's position, orientation, and movement in a 3D scene.
	 */
	class Camera {
	public:
		// The camera's position in 3D space.
		glm::vec3 m_cameraPos{};

		// The direction the camera is facing.
		glm::vec3 m_cameraFront{};

		// The "up" direction of the camera.
		glm::vec3 m_cameraUp{};

		// The camera's movement speed.
		float m_cameraSpeed{};
	public:
		/**
		 * @brief Handles camera movement based on user input.
		 * Captures input from the given GLFW window to control the camera's position and orientation.
		 * @param p_window The GLFW window to capture user input.
		 */
		void Controls(GLFWwindow* p_window);

		Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const float speed);

		/**
		 * @brief Gets the view matrix for the camera.
		 * The view matrix transforms world coordinates to camera coordinates.
		 * @return A glm::mat4 representing the view matrix.
		 */
		[[nodiscard]] glm::mat4 GetViewMatrix() const;

		//! DISCARD IS USED FOR WARNINGS IF VALUES ARE NOT USED
		/**
		 * @brief Gets the projection matrix for the camera.
		 * The projection matrix transforms 3D coordinates into 2D screen space.
		 * @return A glm::mat4 representing the projection matrix.
		 */
		[[nodiscard]] static glm::mat4 GetProjectionMatrix();

		/**
		 * @brief Resets the camera to its default position and orientation.
		 * Useful for returning the camera to its starting state.
		 * @param p_window The GLFW window (used for method calls but not directly in this function).
		 */
		void CameraReset(GLFWwindow* p_window);

		[[nodiscard]] const glm::vec3& GetCamerasPos() const { return m_cameraPos; }
	};
}