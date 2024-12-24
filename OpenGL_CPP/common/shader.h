#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

/// <summary>
/// Loads and compiles shaders from the specified file paths.
/// </summary>
/// <param name="p_vertextFilePath">Path to the vertex shader file.</param>
/// <param name="p_fragmentFilePath">Path to the fragment shader file.</param>
/// <returns>Returns the shader program ID after successfully loading and compiling the shaders.</returns>
GLuint LoadShaders(const char* p_vertextFilePath, const char* p_fragmentFilePath);

#endif // SHADER_H
