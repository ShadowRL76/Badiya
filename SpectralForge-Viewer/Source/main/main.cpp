// Third-party libraries

#include "pch.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <print>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gtx/quaternion.hpp>
#include <stb/stb_image.h>
#include <spdlog/spdlog.h>


#include <spdlog/spdlog.h>

#include <assimp/scene.h>


// SpectralForge-Core headers
#include "Graphics/Shader.h"
#include "Camera/Camera.h"
#include "Graphics/OpenGLUtils.h"
#include "ImGui/ImGuiManager.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Window/WindowManager.h"

#include "Graphics/Renderer.h"
#include "Graphics/Model.h"

#include "Logging.h"

// Standard library
#include <string>

#include "../../../SpectralForge-Core/ApplicationEvent.h"


//TODO: Figure out textures, Clean up Main, and Shader
//TODO: Add shader helper functions
//TODO: Clean Up Mesh and Model as well
// Shader needs to use Modern CPP and same with Mesh and Model

// NOTE FOR CLASS DESIGN:
//
// When you define a default constructor for a class, 
// always consider whether you need to explicitly define or delete:
//  - Copy constructor
//  - Copy assignment operator
//  - Move constructor
//  - Move assignment operator
//
// This ensures you control how objects are copied or moved,
// avoid unintended expensive copies, and maintain resource safety.
//
// If your class manages resources (memory, handles, etc.), 
// explicitly define or delete these to prevent bugs.
//
// For lightweight or POD-like classes, the compiler-generated defaults might suffice.
//
// Review on a per-class basis whether copying/moving makes sense,
// or if you should use references/pointers to avoid copies.


namespace Badiya {
	int Run() 
	{
		OpenGLInit init;
		ImGuiManager guiManager;
		WindowManager windowManager(&init);
		Logging::Init();

		auto window =
			windowManager.CreateAppWindow(3840, 2160, "Graphics Engine",
				nullptr, nullptr);


		BDY_CORE_INFO("Window created: {}x{}", 3840, 2160);

		ImGuiManager::Init(window.get());
		Camera cam{
			glm::vec3(2.5f, 2.0f, -15.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			0.1f
		};

		WindowResizeEvent e(3840, 2160);
		BDY_TRACE(e.ToString());


		GLuint skyboxBuffers[3];
		Renderer::BindBuffersAndGenBuffers(Renderer::BufferType::Skybox, 1, skyboxBuffers);

		stbi_set_flip_vertically_on_load(true);

		//Model model("../SpectralForge-Core/resources/model.obj");
		//Model model1("../SpectralForge-Core/resources/girl.fbx");

		std::string facesCubeMap[6] = {
		"../SpectralForge-Core/resources/blueGalaxyRT.png",
		"../SpectralForge-Core/resources/blueGalaxyLF.png",
		"../SpectralForge-Core/resources/blueGalaxyUP.png",
		"../SpectralForge-Core/resources/blueGalaxyDN.png",
		"../SpectralForge-Core/resources/blueGalaxyFT.png",
		"../SpectralForge-Core/resources/blueGalaxyBK.png"
		};

		Renderer::LoadCubeMap(facesCubeMap);

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
			.Triangle = &translateTriangle };


		GLuint texture;
		Renderer::BindBuffersAndGenBuffers(Renderer::BufferType::Object, 1, &texture);


		float yRotationAngle = 1.0f;

		BDY_CORE_INFO("Badiya Viewer started");


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

			float angle = glm::radians(yRotationAngle);
			glm::vec3 rotationVector(0.0f, 1.0f, 0.0f);

			glm::quat q = angleAxis(angle, rotationVector);
			glm::mat4 rotationMat = toMat4(q);

			// creates a model matrix. This matrix is used to position,
			// scale, and rotate objects in the world. By default, it's the identity matrix (1.0f),
			// which means no transformation. If you wanted to move or rotate your object, you would modify this matrix.
			auto Model = glm::mat4(1.0f);
			Model = translate(Model, translateSquareOne) * rotationMat;
			glm::mat4 MVPOne = Camera::GetProjectionMatrix() * cam.GetViewMatrix() * Model; // Combine them into the MVP matrix

			Model = glm::mat4(1.0f);
			Model = translate(Model, translateSquareTwo) * rotationMat;
			glm::mat4 MVPThree = Camera::GetProjectionMatrix() * cam.GetViewMatrix() * Model; // Combine them into the MVP matrix

			// Get the location of the MVP uniform
			Model = glm::mat4(1.0f);
			Model = translate(Model, translateTriangle) * rotationMat;
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

				//model.Draw(shader1);

				//model1.Draw(shader1);

			}
			else
			{
				static const auto runOnce = [] { BDY_CORE_INFO("Shader 2 Disabled!"); return true; }();
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

				glBindVertexArray(skyboxBuffers[0]);
				glActiveTexture(GL_TEXTURE0);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
				glDepthFunc(GL_LESS);
			}
			else if (!guiManager.shader2Enabled)
			{
				static const auto runOnce = [] { BDY_CORE_INFO("Shader 2 Disabled!"); return true; }();
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
		return 0;
	}
}

int main()
{
	return Badiya::Run();
}