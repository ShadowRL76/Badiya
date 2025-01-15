#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Camera/Camera.h"

/*
		auto Model = glm::mat4(1.0f);
		glm::mat4 MVPOne = cam.GetProjectionMatrix() * cam.GetViewMatrix() * Model; // Combine them into the MVP matrix
*/

class Shape {
private:
	float angle{};
protected:
	Camera cam;
	glm::vec3 spawnTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 viewProjection = cam.GetProjectionMatrix() * cam.GetViewMatrix() * model;
	glm::mat4 mvp = viewProjection;

public:

	Shape() : angle(glm::radians(0.0f)) {}

	virtual void draw() {}

	void setAngle(const float degrees) {
		angle = glm::radians(degrees);
		updateViewProjection();
	}

	void setSpawnTranslation(const glm::vec3& translation) {
		spawnTranslation = translation;
		updateViewProjection();
	}

	void setModel(const glm::mat4& Model) {
		model = Model;
		updateViewProjection();
	}

	glm::mat4 updateViewProjection() {
		viewProjection = cam.GetProjectionMatrix() * cam.GetViewMatrix() * model;
		return viewProjection;
	}

	void setMVPMatrix(const glm::mat4& MVP) {
		mvp = MVP;
	}
};

class Cube : public Shape
{
public:
	void draw() override {}
};

class Triangle : public Shape
{
public:
	void draw() override {}
};

template <typename T>
class Renderer
{
public:
	Renderer();
	void draw() const;
private:
	void set_shader();
};
