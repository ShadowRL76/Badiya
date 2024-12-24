#include "OpenGLUtils.h" 
#include "ImGuiManager.h"

ImGuiManager::ImGuiManager(){}
 
void ImGuiManager::Init(GLFWwindow* p_window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::GetIO().FontGlobalScale = 3.0f;
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiManager::RenderUI(Camera& camera, GLFWwindow* p_window, glm::vec3& translateSquareOne, glm::vec3& translateSquareTwo, glm::vec3& translateTriangle)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("My Window");
    ImGui::Text("OpenGL_Version: %s", p_init->GetOpenGLVersion());
    ImGui::SliderFloat3("Translate Square One", glm::value_ptr(translateSquareOne), -20.0f, 20.0f);
    ImGui::SliderFloat3("Translate Square Two", glm::value_ptr(translateSquareTwo), -20.0f, 20.0f);
    ImGui::SliderFloat3("Translate Triangle", glm::value_ptr(translateTriangle), -20.0f, 20.0f);
    if (ImGui::Button("Reset"))
    {
        translateSquareOne = glm::vec3(-3.0f, 0.0f, 0.0f);
        translateSquareTwo = glm::vec3(6.0f, 0.0f, 0.0f);
        translateTriangle = glm::vec3(2.0f, 0.0f, 0.0f);
        camera.CameraReset(p_window);
    }
    if (ImGui::Button("Add Square"))
    {
        //Add a square Soon! Clean up code for this and add a draw new objects function!
    }
    if (ImGui::Button("Close Me"))
    {
        glfwSetWindowShouldClose(p_window, true);
    }

    ImGui::Text("FPS %f", ImGui::GetIO().Framerate);
    ImGui::Text("Application average %.3f", 1000.0f / ImGui::GetIO().Framerate);

    ImGui::End(); 
    ImGui::Render();  
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  
}

ImGuiManager::~ImGuiManager()
{
    ImGui_ImplOpenGL3_Shutdown(); 
    ImGui_ImplGlfw_Shutdown(); 
    ImGui::DestroyContext(); 
}
