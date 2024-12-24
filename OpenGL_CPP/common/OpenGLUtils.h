#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

/// <summary>
/// A utility class responsible for initializing OpenGL and managing OpenGL context.
/// </summary>
class OpenGLInit {
public:
    /// <summary>
    /// Constructor for the OpenGLInit class.
    /// Initializes OpenGL and sets up the necessary context, such as GLFW and GLEW.
    /// </summary>
    OpenGLInit();
    void GlewInit();
    GLubyte* GetOpenGLVersion();
};

#endif
