#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "dependencies/imgui/imgui.h"

#include "common/Shader.h"
#include "common/Camera.h"
#include "common/OpenGLUtils.h"
#include "common/WindowManager.h"
#include "common/ImGuiManager.h"
#include "common/VertexBuffer.h"
#include "common/IndexBuffer.h"

int main()
{
	OpenGLInit init;
	ImGuiManager ImGuiManager;
	WindowManager windowManager(&init);

	auto window = 
		windowManager.CreateWindow(3840, 2160, "Graphics Engine", nullptr, nullptr);

	ImGuiManager::Init(window.get());
	Camera cam;

	static constexpr float skyboxVertices[]
	{
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f
	};

	static constexpr unsigned int skyboxIndices[]
	{
		// Right face
		1, 2, 6,
		6, 5, 1,
		// Left face
		0, 4, 7,
		7, 3, 0,
		// Top face
		4, 5, 6,
		6, 7, 4,
		// Bottom face
		0, 1, 2,
		2, 3, 0,
		// Back face
		3, 2, 6,
		6, 7, 3,
		// Front face
		0, 1, 5,
		5, 4, 0
	};

	
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);

	glBindVertexArray(skyboxVAO);

	// Bind and set vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	// Bind and set index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

	glBindVertexArray(0);


	std::string facesCubeMap[6] = {
		"resources/right.jpg",
		"resources/left.jpg",
		"resources/top.jpg",
		"resources/bottom.jpg",
		"resources/front.jpg",
		"resources/back.jpg"
	};


	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubeMap[i].c_str(), &width, &height, &nrChannels,0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cannot Load Textures for cube map: "<< facesCubeMap[i] << "\n"; 
			stbi_image_free(data); 
		}
	}
	


	Shader shader2(
		"\common\\skybox.vertexshader",
		"\common\\skybox.fragmentshader");
		
	glm::vec3 translateSquareOne(-3.0f, 0.0f, 0.0f);
	glm::vec3 translateSquareTwo(6.0f, 0.0f, 0.0f);
	glm::vec3 translateTriangle(2.0f, 0.0f, 0.0f);
	ImGuiManager::Params pm{ .camera = cam, .p_window = window.get(),
		.SquareOne = translateSquareOne, .SquareTwo = translateSquareTwo, .Triangle = translateTriangle };
	do {
		//Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//shader1.Activate();
		shader2.Activate();
		glUniform1i(glGetUniformLocation(shader2.ID, "skybox"), 0); 
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		int width, height;

		glfwGetFramebufferSize(window.get(), &width, &height);

		//uint32_t MatrixIDS = glGetUniformLocation(shader1.ID, "MVP");

		cam.Controls(window.get());
		ImGuiManager.RenderUI(pm);

		
		glDepthFunc(GL_LEQUAL);
		shader2.Activate(); 
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		view = glm::mat4(glm::mat4(lookAt(*cam.m_cameraPos, *cam.m_cameraPos + *cam.m_cameraFront, *cam.m_cameraUp)));
		projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader2.ID, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader2.ID, "projection"), 1, GL_FALSE, value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		

		glDepthFunc(GL_LESS);
		

		// Swap buffers
		glfwSwapBuffers(window.get());
		glfwPollEvents();

		//Enabled so gpu cant render inside the cubes
		//glEnable(GL_CULL_FACE);
		//glfwSwapInterval(0); // Disable V-Sync
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window.get()) == 0);
}