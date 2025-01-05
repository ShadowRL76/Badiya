#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

/// <summary>
/// A utility class responsible for initializing OpenGL and managing the OpenGL context.
/// </summary>
class OpenGLInit {
private:
	/// <summary>
	/// Stores the OpenGL version string after initialization.
	/// This can be used to verify that the context is properly set up.
	/// </summary>
	GLubyte* openGLVersion{}; // You can uncomment or implement if applicable in private use.

public:
	/// <summary>
	/// Constructor for the OpenGLInit class.
	/// Initializes OpenGL and sets up the necessary context, such as GLFW and GLEW.
	/// </summary>
	OpenGLInit();

	/// <summary>
	/// Initializes the GLEW library to ensure proper functionality of OpenGL extensions.
	/// </summary>
	void GlewInit();

	/// <summary>
	/// Retrieves the current OpenGL version as a string.
	/// </summary>
	/// <returns>A pointer to a string containing the OpenGL version.</returns>
	GLubyte* GetOpenGLVersion();
};

#endif // OPENGL_UTILS_H
