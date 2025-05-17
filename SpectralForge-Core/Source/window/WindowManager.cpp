#include "WindowManager.h"

std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>
WindowManager::CreateWindow(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(
		glfwCreateWindow(width, height, title, monitor, share),
		glfwDestroyWindow
	);

	if (window == nullptr)
	{
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		quick_exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window.get()); // Initialize GLEW

	OpenGLInit::GlewInit();

	glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);
	return window;
}