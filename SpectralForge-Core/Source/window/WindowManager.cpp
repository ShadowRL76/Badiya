#include "WindowManager.h"

#include <spdlog/spdlog.h>

std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> 
WindowManager::CreateAppWindow(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(
		glfwCreateWindow(width, height, title, monitor, share),
		glfwDestroyWindow
	);

	if (window == nullptr)
	{
		//spdlog::critical("Failed to open GLFW window.{}", window)
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		quick_exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window.get()); // Initialize GLEW

	p_init->GlewInit();

	glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);
	return window;
}
