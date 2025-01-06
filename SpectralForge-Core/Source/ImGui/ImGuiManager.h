#ifndef IM_GUI_MANAGER_H
#define IM_GUI_MANAGER_H


#include "Graphics/OpenGLUtils.h"    
#include "Camera/Camera.h"          

#include <imgui/imgui.h>            
#include <imgui/imgui_impl_glfw.h>  
#include <imgui/imgui_impl_opengl3.h> 

#include <glm/glm.hpp>             
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>     

/**
 * @class ImGuiManager
 * @brief Manages the integration and rendering of ImGui UI components in an OpenGL application.
 */
class ImGuiManager
{
public:
    /**
     * @struct Params
     * @brief A helper structure to encapsulate parameters needed for rendering the ImGui UI.
     */
    struct Params {
        Camera& camera;          ///< Reference to the Camera object used for scene manipulation.
        GLFWwindow* p_window;    ///< Pointer to the GLFW window used for rendering.
        glm::vec3& SquareOne;    ///< Translation vector for the first square object.
        glm::vec3& SquareTwo;    ///< Translation vector for the second square object.
        glm::vec3& Triangle;     ///< Translation vector for the triangle object.
    };

private:
    OpenGLInit* p_init{}; ///< Pointer to an OpenGL initialization object for managing OpenGL settings.

    /**
     * @brief Displays the ImGui user guide window.
     * Provides general instructions for interacting with the UI.
     */
    static void ShowUserGuide();

    /**
     * @brief Displays controls for manipulating objects and the camera.
     * @param camera Reference to the Camera object.
     * @param p_window Pointer to the GLFW window for user input.
     * @param SquareOne Translation vector for the first square object.
     * @param SquareTwo Translation vector for the second square object.
     * @param Triangle Translation vector for the triangle object.
     */
    void ShowControlsSection(const Camera& camera, GLFWwindow* p_window, glm::vec3& SquareOne, glm::vec3& SquareTwo, glm::vec3& Triangle) const;

public:
    /**
     * @brief Constructor to initialize the ImGuiManager with an OpenGLInit object.
     * @param p_init Pointer to the OpenGL initialization object.
     */
    explicit ImGuiManager(OpenGLInit* p_init) : p_init(p_init) {}

    /**
     * @brief Default constructor for the ImGuiManager class.
     * Initializes an empty ImGuiManager instance.
     */
    ImGuiManager() = default;

    /**
     * @brief Initializes the ImGui context and sets up OpenGL and GLFW bindings.
     * @param p_window Pointer to the GLFW window used for rendering the ImGui UI.
     */
    static void Init(GLFWwindow* p_window);

    /**
     * @brief Renders the ImGui UI for user interaction with the application.
     * Allows users to manipulate objects like squares and triangles via the UI.
     * @param pm A Params structure containing necessary rendering parameters.
     */
    void RenderUI(const Params& pm) const;

    /**
     * @brief Destructor for the ImGuiManager class.
     * Cleans up and shuts down the ImGui context to free resources.
     */
    ~ImGuiManager();
};

#endif // !IM_GUI_MANAGER_H
