// Third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <spdlog/spdlog.h>

// SpectralForge-Core headers
#include "Graphics/Shader.h"
#include "Camera/Camera.h"
#include "Graphics/OpenGLUtils.h"
#include "ImGui/ImGuiManager.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Window/WindowManager.h"

// Standard library
#include <iostream>
#include <string>

int main()
{

	OpenGLInit init;
	ImGuiManager guiManager;
	WindowManager windowManager(&init);

	auto window =
		windowManager.CreateAppWindow(3840, 2160, "Graphics Engine", 
			nullptr, nullptr);
	spdlog::info("Window created: {}x{}", 3840, 2160);

	ImGuiManager::Init(window.get());
	Camera cam{
		glm::vec3(2.5f, 2.0f, -15.0f), 
		glm::vec3(0.0f, 0.0f, 1.0f),  
		glm::vec3(0.0f, 1.0f, 0.0f),   
		0.1f                           
	};

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
		"../SpectralForge-Core/resources/blueGalaxyRT.png",
		"../SpectralForge-Core/resources/blueGalaxyLF.png",
		"../SpectralForge-Core/resources/blueGalaxyUP.png",
		"../SpectralForge-Core/resources/blueGalaxyDN.png",
		"../SpectralForge-Core/resources/blueGalaxyFT.png",
		"../SpectralForge-Core/resources/blueGalaxyBK.png"
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
		unsigned char* data = stbi_load(facesCubeMap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			spdlog::info("Loaded texture '{}'", facesCubeMap[i]);
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
			spdlog::error("[CubeMap] Failed to load texture '{}', index {}.", facesCubeMap[i], i);
			stbi_image_free(data);
		}
	}

	unsigned int VertexArrayID{};
	glGenVertexArrays(1, &VertexArrayID);

	VertexBuffer vb;
	int vbSize = vb.GetCubeSize();
	float* vbArr = vb.Cube();
	unsigned long long vbSizeInBytes = vbSize * sizeof(float);
	VertexBuffer vertexBuffer(vbArr, vbSizeInBytes);

	IndexBuffer ib;
	int ibSize = ib.GetCubeSize();
	int* ibArr = ib.Cube();
	unsigned long long sizeInBytes = ibSize * sizeof(float);
	IndexBuffer indexBuffer(ibArr, sizeInBytes);

	Shader shader1(
		"../SpectralForge-Core/Source/Shaders/SimpleFragmentShader.fragmentshader",
		"../SpectralForge-Core/Source/Shaders/SimpleVertexShader.vertexshader");
	Shader shader2(
		"../SpectralForge-Core/Source/Shaders/skybox.vertexshader",
		"../SpectralForge-Core/Source/Shaders/skybox.fragmentshader");

	glm::vec3 translateSquareOne(-3.0f, 0.0f, 0.0f);
	glm::vec3 translateSquareTwo(6.0f, 0.0f, 0.0f);
	glm::vec3 translateTriangle(2.0f, 0.0f, 0.0f);

	ImGuiManager::Params pm{ .camera = &cam, .p_window = window.get(),
		.SquareOne = &translateSquareOne, .SquareTwo = &translateSquareTwo,
		.Triangle = &translateTriangle}; 



	int widthImg{}, heightImg{}, numColCh{};
	unsigned char* bytes = stbi_load("../SpectralForge-Core/resources/img.jpg",
		&widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
	float yRotationAngle = 1.0f;

	spdlog::info("SpectralForge Viewer started");

	do {
		//Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		int width, height;

		glfwGetFramebufferSize(window.get(), &width, &height);

		GLint MatrixIDS = glGetUniformLocation(shader1.ID, "MVP");

		cam.Controls(window.get());

		glm::mat4 rotationMatrix = rotate(glm::mat4(1.0f), 
			glm::radians(yRotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)); 

		// creates a model matrix. This matrix is used to position,
		// scale, and rotate objects in the world. By default, it's the identity matrix (1.0f),
		// which means no transformation. If you wanted to move or rotate your object, you would modify this matrix.
		auto Model = glm::mat4(1.0f);
		Model = translate(Model, translateSquareOne) * rotationMatrix;
		glm::mat4 MVPOne = Camera::GetProjectionMatrix() * cam.GetViewMatrix() * Model; // Combine them into the MVP matrix

		Model = glm::mat4(1.0f);
		Model = translate(Model, translateSquareTwo) * rotationMatrix;  
		glm::mat4 MVPThree = Camera::GetProjectionMatrix() * cam.GetViewMatrix() * Model; // Combine them into the MVP matrix

		// Get the location of the MVP uniform
		Model = glm::mat4(1.0f);
		Model = translate(Model, translateTriangle);
		glm::mat4 MVPTwo = Camera::GetProjectionMatrix() * cam.GetViewMatrix() * Model; // Combine them into the MVP matrix

		glEnableVertexAttribArray(0); // position
		glEnableVertexAttribArray(1); // color

		if (guiManager.CubeRotationEnabled)
		{
			yRotationAngle += 0.50f;
		}

		if (guiManager.shader1Enabled) {
			vertexBuffer.Bind();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<const void*>(3 * sizeof(float)));

			shader1.Activate();
			glUniform1i(glGetUniformLocation(shader1.ID, "textureSampler"), 0);

			indexBuffer.Bind();

			glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, value_ptr(MVPOne));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

			glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, value_ptr(MVPTwo));
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, value_ptr(MVPThree));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);



		}

		glDepthFunc(GL_LEQUAL);
		//glm::mat4 view(1.0f);
		//glm::mat4 projection(1.0f);
		//view = glm::mat4(glm::mat4(lookAt(*cam.m_cameraPos, *cam.m_cameraPos + *cam.m_cameraFront, *cam.m_cameraUp)));

		//MAIN view and projection for skybox
		auto view = glm::mat4(glm::mat3(cam.GetViewMatrix()));
		auto projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
		 
		if (guiManager.shader2Enabled) {
			shader2.Activate();
			glUniformMatrix4fv(glGetUniformLocation(shader2.ID, "view"), 1, GL_FALSE, value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shader2.ID, "projection"), 1, GL_FALSE, value_ptr(projection));

			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);

			glDepthFunc(GL_LESS);
			glBindVertexArray(VertexArrayID);
		}

		guiManager.RenderUI(pm);

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