#pragma once


namespace Badiya {
	class Camera;

class CameraController
{
private:
	Camera& m_camera;
public:
	explicit CameraController(Camera& camera);

	glm::vec3 MoveForward(const float speed);
	glm::vec3 MoveLeft(const float speed);
	glm::vec3 MoveRight(const float speed);
	glm::vec3 MoveBackwards(const float speed);
	glm::vec3 MoveUp(const float Position);
	glm::vec3 MoveDown(const float Position);

};
}