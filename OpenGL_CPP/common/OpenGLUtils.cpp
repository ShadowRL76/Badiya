#include "OpenGLUtils.h"


OpenGLInit::OpenGLInit()
{
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Don't want the old OpenGL 
}


void OpenGLInit::GlewInit()
{
	glewExperimental = true; // Needed for core profile  
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		exit(EXIT_FAILURE);
	}
}

GLubyte* OpenGLInit::GetOpenGLVersion()
{
	const GLubyte* version = glGetString(GL_VERSION);
	return (GLubyte*)version; 
}


