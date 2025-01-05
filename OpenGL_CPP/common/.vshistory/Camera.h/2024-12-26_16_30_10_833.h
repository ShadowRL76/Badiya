#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

/// <summary>
/// Camera class that manages camera movement and viewing in a 3D scene.
/// </summary>
class Camera {
private:
    /// <summary>
    /// Camera movement speed.
    /// </summary>
    std::unique_ptr<float> m_cameraSpeed{};

    /// <summary>
    /// Camera position in the 3D space.
    /// </summary>
    std::unique_ptr<glm::vec3> m_cameraPos{};

    /// <summary>
    /// Direction the camera is facing.
    /// </summary>
    std::unique_ptr<glm::vec3> m_cameraFront{};

    /// <summary>
    /// The "up" direction vector for the camera.
    /// </summary>
    std::unique_ptr<glm::vec3> m_cameraUp{};

public:
    /// <summary>
    /// Constructor for the Camera class.
    /// Initializes camera position, front, up vectors, and movement speed.
    /// </summary>
    /// <param name="window">The GLFW window used to capture user input.</param>
    Camera() = default;

    /// <summary>
    /// Handles camera movement and control based on user input.
    /// </summary>
    /// <param name="window">The GLFW window used to capture user input.</param>
    void Controls(GLFWwindow* window) const;

    /// <summary>
    /// Returns the camera's view matrix.
    /// The view matrix is used to transform world coordinates to camera coordinates.
    /// </summary>
    /// <returns>A glm::mat4 representing the camera's view matrix.</returns>
    [[nodiscard]] glm::mat4 GetViewMatrix() const;

    /// <summary>
    /// Returns the camera's projection matrix.
    /// The projection matrix defines how the 3D scene is projected onto the 2D screen.
    /// </summary>
    /// <returns>A glm::mat4 representing the camera's projection matrix.</returns>
    [[nodiscard]] glm::mat4 GetProjectionMatrix();

    /// <summary>
    /// Resets the camera to its initial position and orientation.
    /// </summary>
    /// <param name="window">The GLFW window (required for calling other methods, but not used directly in this function).</param>
    void CameraReset(GLFWwindow* window) const;
};

// Factory function to create a Camera object
/// <summary>
/// Creates and returns a Camera object initialized with the given window.
/// </summary>
/// <param name="window">The GLFW window to be passed to the Camera constructor.</param>
/// <returns>A Camera object initialized with the given window.</returns>
Camera camera(GLFWwindow* window);

#endif // CAMERA_H
