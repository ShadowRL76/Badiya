#include "ImGuiManager.h"

#include "Graphics/Renderer.h"

void ImGuiManager::Init(GLFWwindow* p_window)
{
	ImGui::CreateContext();
	ImGuiIO const& io = ImGui::GetIO(); (void)io;
	ImGui::GetIO().FontGlobalScale = 3.0f;
	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiManager::RenderUI(const Params& pm)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("My Window");
	if (ImGui::CollapsingHeader("Help"))
	{
		ImGui::SeparatorText("ABOUT THIS ENGINE:");
		ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
		ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
		ImGui::BulletText("The \"Tools\" menu above gives access to: ");
		ImGui::Indent();
		ImGui::Indent();
		ImGui::BulletText("About Box");
		ImGui::BulletText("Style Editor");
		ImGui::BulletText("and Metrics/Debugger (general purpose Dear ImGui debugging tool).");
		ImGui::Unindent();
		ImGui::Unindent();

		ImGui::SeparatorText("PROGRAMMER GUIDE:");
		ImGui::Indent();
		ImGui::Indent();
		ImGui::BulletText("Read the FAQ at ");
		ImGui::SameLine(0, 0);
		ImGui::TextLinkOpenURL("https://github.com/ShadowRL76/SpectralForge/blob/master/README.md");
		ImGui::Unindent();
		ImGui::Unindent();
		ImGui::SeparatorText("USER GUIDE:");
		ShowUserGuide();
	}
	ShowControlsSection(pm.camera, pm.p_window, pm.SquareOne, pm.SquareTwo, pm.Triangle);
	DebugTab(pm.camera);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::ShowUserGuide()
{
	ImGui::BulletText("Double-click on title bar to collapse window.");
	ImGui::BulletText("Click and drag on lower corner to resize window");
	ImGui::Indent();
	ImGui::Indent();
	ImGui::BulletText("(double-click to auto fit window to its contents).");
	ImGui::Unindent();
	ImGui::Unindent();
	ImGui::BulletText("Controls:");
	ImGui::Indent();
	ImGui::Indent();
	ImGui::BulletText("W, A, S, D keys: Navigate.");
	ImGui::BulletText("K key: Look right.");
	ImGui::BulletText("J key: Look left.");
	ImGui::BulletText("Space: Go up.");
	ImGui::BulletText("L_Shift: Go down.");
	ImGui::BulletText("L_CTRL: Look Up.");
	ImGui::BulletText("L_ALT: Look down.");
	ImGui::BulletText("Escape key: Exit.");
	ImGui::Unindent();
	ImGui::Unindent();
}

void ImGuiManager::ShowControlsSection(const Camera& camera, GLFWwindow* p_window,
	glm::vec3& SquareOne, glm::vec3& SquareTwo, glm::vec3& Triangle) 
{
	if (ImGui::CollapsingHeader("Controls"))
	{
		ImGui::SliderFloat3("Translate Square One", value_ptr(SquareOne), -20.0f, 20.0f);
		ImGui::SliderFloat3("Translate Square Two", value_ptr(SquareTwo), -20.0f, 20.0f);
		ImGui::SliderFloat3("Translate Triangle", value_ptr(Triangle), -20.0f, 20.0f);
		if (ImGui::Button("Reset"))
		{
			SquareOne = glm::vec3(-3.0f, 0.0f, 0.0f);
			SquareTwo = glm::vec3(6.0f, 0.0f, 0.0f);
			Triangle = glm::vec3(2.0f, 0.0f, 0.0f);
			 
			CubeRotationEnabled = false;
			camera.CameraReset(p_window);
		}
		if (ImGui::Button("Rotate Cubes 360")) 
		{
			CubeRotationEnabled = true;
		}

		if (ImGui::Button("Add Square"))
		{
		}
		if (ImGui::Button("Close Me"))
		{
			glfwSetWindowShouldClose(p_window, true);
		}
	}
}

void ImGuiManager::DebugTab(const Camera& camera)
{
	static bool wireFrameMode = false;

	if (ImGui::CollapsingHeader("Debug"))
	{
		ImGui::Text("OpenGL_Version: %s", p_init->GetOpenGLVersion());
		ImGui::Text("FPS %f", ImGui::GetIO().Framerate);
		ImGui::Text("Application average %.3f", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("Cameras Position %f, %f, %f", camera.m_cameraPos->x, camera.m_cameraPos->y, camera.m_cameraPos->z);

		if (ImGui::Button("Disable Skybox Shader"))
		{
			shader2Enabled = !shader2Enabled;
		}
		if (ImGui::Button("Disable Cubes Shader"))
		{
			shader1Enabled = !shader1Enabled;
		}

		if (ImGui::Checkbox("WireFrame Mode", &wireFrameMode))
		{
			if (wireFrameMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	}
}

ImGuiManager::~ImGuiManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}