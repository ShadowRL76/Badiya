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

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif