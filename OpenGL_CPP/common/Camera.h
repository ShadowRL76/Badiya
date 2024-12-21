#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


class Camera {
private:
    std::unique_ptr<float> cameraSpeed;
    std::unique_ptr< glm::vec3> cameraPos;
    std::unique_ptr< glm::vec3> cameraFront;
    std::unique_ptr< glm::vec3> cameraUp;

public:
    Camera(GLFWwindow* window);
    void Controls(GLFWwindow* window) const;
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix();
    void CameraReset(GLFWwindow* window) const; 
  
};

Camera camera(GLFWwindow* window);
#endif // CAMERA_H
