#pragma once

namespace Badiya
{


	/**
	 * @brief Reads the contents of a file into a string.
	 * @param filename The path to the file.
	 * @return A string containing the contents of the file.
	 */
	std::string get_file_contents(const char* filename);

	/**
	 * @class Shader
	 * @brief Represents an OpenGL Shader Program, managing the vertex and fragment shaders.
	 */
	class Shader {
	public:
		/**
		 * @brief The unique identifier for the OpenGL Shader Program.
		 */
		GLuint ID;

		/**
		 * @brief Constructs the Shader Program from a vertex shader file and a fragment shader file.
		 * @param vertexFile Path to the vertex shader source file.
		 * @param fragmentFile Path to the fragment shader source file.
		 */
		Shader(const char* vertexFile, const char* fragmentFile);

		/**
		 * @brief Activates the Shader Program for use in rendering.
		 */
		void Activate() const;

		/**
		 * @brief Deletes the Shader Program and frees resources.
		 */
		void Delete() const;

	private:
		/**
		 * @brief Checks if the given shader or program has compiled/linked correctly.
		 * @param shader The shader or program ID to check.
		 * @param type The type of shader ("VERTEX", "FRAGMENT", or "PROGRAM").
		 */
		static void compileErrors(unsigned int shader, const char* type);
	};
}