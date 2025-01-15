#pragma once

#include "Graphics/OpenGLUtils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

/**
 * @class WindowManager
 * @brief A class responsible for managing GLFW windows, including creation and cleanup.
 */
class WindowManager {
private:
	/**
	 * @brief Pointer to an OpenGL initialization object.
	 * Used to manage OpenGL settings and ensure proper initialization.
	 */
	OpenGLInit* p_init{};
	static WindowManager* instance;

public:
	/**
	 * @brief Constructor for the WindowManager class.
	 * Initializes the OpenGLInit object to manage OpenGL context.
	 * @param p_init A pointer to an OpenGLInit object.
	 */
	WindowManager(OpenGLInit* p_init) : p_init(p_init) {}

	/**
	 * @brief Creates a new GLFW window with the specified parameters.
	 * Uses a unique pointer to automatically manage memory and ensure cleanup.
	 * @param width The width of the window in pixels.
	 * @param height The height of the window in pixels.
	 * @param title The title of the window.
	 * @param monitor The monitor to use for fullscreen mode, or NULL for windowed mode.
	 * @param share Another window whose OpenGL context to share resources with, or NULL for no sharing.
	 * @return A unique pointer to the created GLFWwindow, automatically cleaned up when out of scope.
	 */
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>
		CreateWindow(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
};
