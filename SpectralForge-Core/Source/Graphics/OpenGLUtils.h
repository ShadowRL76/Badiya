#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <mutex>

/**
 * @class OpenGLInit
 * @brief A utility class to initialize OpenGL, GLEW, and manage the OpenGL context.
 */
class OpenGLInit {
public:
	/**
	 * @brief Stores the OpenGL version string after initialization.
	 * Useful for confirming that the OpenGL context has been properly set up.
	 */
	GLubyte* openGLVersion{};

	/**
	 * @brief Constructor for the OpenGLInit class.
	 * Responsible for setting up the OpenGL context and ensuring necessary libraries (like GLFW and GLEW) are initialized.
	 */
	OpenGLInit();

	/**
	 * @brief Initializes the GLEW library.
	 * Ensures that OpenGL extensions are properly loaded and ready for use.
	 * This must be called after an OpenGL context has been created (e.g., using GLFW).
	 */
	static void GlewInit();

	/**
	 * @brief Retrieves the current OpenGL version as a string.
	 * @return A pointer to a string containing the OpenGL version.
	 */
	static GLubyte* GetOpenGLVersion();
};
