#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "OpenGLUtils.h"



/// <summary>
/// A class responsible for managing GLFW windows, including creation and cleanup.
/// </summary>
class WindowManager {
private:
    /// <summary>
    /// Pointer to an OpenGL initialization object.
    /// Used to manage OpenGL settings and ensure proper initialization.
    /// </summary>
    OpenGLInit* p_init{}; 
    /// <summary>
    /// Creates a new GLFW window with the specified parameters.
    /// Uses a unique pointer to automatically manage memory and ensure cleanup.
    /// </summary>
    /// <param name="width">The width of the window in pixels.</param>
    /// <param name="height">The height of the window in pixels.</param>
    /// <param name="title">The title of the window.</param>
    /// <param name="monitor">The monitor to use for fullscreen mode, or NULL for windowed mode.</param>
    /// <param name="share">Another window whose OpenGL context to share resources with, or NULL for no sharing.</param>
    /// <returns>A unique pointer to the created GLFWwindow, automatically cleaned up when out of scope.</returns>
public:
    WindowManager(OpenGLInit* p_init) : p_init(p_init) {} 
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>
        CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
};



#endif
