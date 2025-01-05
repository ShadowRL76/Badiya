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
		windowManager.CreateWindow(1920, 1080, "Graphics Engine", nullptr, nullptr);

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

	
	static constexpr  float s_VertexBufferDataCube[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	static constexpr unsigned int s_IndexBufferDataCube[] = {
	0, 1, 2,   // Triangle 1
	3, 4, 5,   // Triangle 2
	6, 7, 8,   // Triangle 3
	9, 10, 11, // Triangle 4
	12, 13, 14,// Triangle 5
	15, 16, 17,// Triangle 6
	18, 19, 20,// Triangle 7
	21, 22, 23,// Triangle 8
	24, 25, 26,// Triangle 9
	27, 28, 29,// Triangle 10
	30, 31, 32,// Triangle 11
	33, 34, 35 // Triangle 12
	};

	static constexpr float s_ColorBufferData[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
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
		"resources\\right.jpg",
		"resources\\left.jpg",
		"resources\\top.jpg",
		"resources\\bottom.jpg",
		"resources\\front.jpg",
		"resources\\back.jpg"
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
	

	
	unsigned int VertexArrayID{};
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	VertexBuffer vertexBuffer(s_VertexBufferDataCube, sizeof(s_VertexBufferDataCube));
	VertexBuffer vertexBufferTriangle(s_VertexBufferDataCube, sizeof(s_VertexBufferDataCube));
	VertexBuffer vertexBufferSquareTwo(s_VertexBufferDataCube, sizeof(s_VertexBufferDataCube));

	IndexBuffer indexBufferSquareOne(s_IndexBufferDataCube, sizeof(s_IndexBufferDataCube));
	IndexBuffer indexBufferTriangle(s_IndexBufferDataCube, sizeof(s_IndexBufferDataCube));
	IndexBuffer indexBufferSquareTwo(s_IndexBufferDataCube, sizeof(s_IndexBufferDataCube));

	uint32_t colorBuffer{};
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_ColorBufferData), &s_ColorBufferData, GL_STATIC_DRAW);
	Shader shader1(
		"\common\\SimpleVertexShader.vertexshader",
		"\common\\SimpleFragmentShader.fragmentshader");
	
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
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		int width, height;

		glfwGetFramebufferSize(window.get(), &width, &height);

		GLint MatrixIDS = glGetUniformLocation(shader1.ID, "MVP");

		cam.Controls(window.get());
		ImGuiManager.RenderUI(pm);


		// creates a model matrix. This matrix is used to position,
		// scale, and rotate objects in the world. By default, it's the identity matrix (1.0f),
		// which means no transformation. If you wanted to move or rotate your object, you would modify this matrix.
		auto ModelSquareOne = glm::mat4(1.0f);
		ModelSquareOne = translate(ModelSquareOne, translateSquareOne);
		glm::mat4 MVPOne = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelSquareOne; // Combine them into the MVP matrix

		auto ModelSquareTwo = glm::mat4(1.0f);
		ModelSquareTwo = translate(ModelSquareTwo, translateSquareTwo);
		glm::mat4 MVPThree = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelSquareTwo; // Combine them into the MVP matrix

		// Get the location of the MVP uniform
		auto ModelTriangle = glm::mat4(1.0f);
		constexpr float angle(glm::radians(90.0));
		ModelTriangle = rotate(ModelTriangle, angle, glm::vec3(0, 1, 0));
		ModelTriangle = translate(ModelTriangle, translateTriangle);
		glm::mat4 MVPTwo = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelTriangle; // Combine them into the MVP matrix


		glEnableVertexAttribArray(0); // position
		glEnableVertexAttribArray(1); // color

		vertexBuffer.Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		shader1.Activate();

		indexBufferSquareOne.Bind();
		glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, value_ptr(MVPOne));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

		indexBufferTriangle.Bind();
		glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, value_ptr(MVPTwo));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);

		indexBufferSquareTwo.Bind();
		glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, value_ptr(MVPThree));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		
		glDepthFunc(GL_LEQUAL);
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		view = glm::mat4(glm::mat4(lookAt(*cam.m_cameraPos, *cam.m_cameraPos + *cam.m_cameraFront, *cam.m_cameraUp)));
		projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

		shader2.Activate(); 
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