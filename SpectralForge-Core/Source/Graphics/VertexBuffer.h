#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/**
 * @class VertexBuffer
 * @brief Represents a vertex buffer used in OpenGL for storing vertex data.
 */
class VertexBuffer {
private:
	/**
	 * @brief The OpenGL renderer ID for the vertex buffer.
	 */
	unsigned int m_RendererID;

	float* arr = nullptr;

public:
	VertexBuffer() = default;
	/**
	 * @brief Constructor that creates a VertexBuffer from the provided vertex data.
	 * Initializes the buffer and stores the vertex data in OpenGL.
	 * @param p_data A pointer to the vertex data array.
	 * @param size The size of the vertex data in bytes.
	 */
	VertexBuffer(const void* p_data, const unsigned long long size);

	/**
	 * @brief Destructor that cleans up the vertex buffer resources.
	 */
	~VertexBuffer();

	float* Cube();

	int GetCubeSize();

	/**
	 * @brief Binds the vertex buffer for use in OpenGL.
	 * This function makes the buffer the current active buffer for OpenGL operations.
	 */
	void Bind() const;

	/**
	 * @brief Unbinds the vertex buffer, making it no longer active in OpenGL.
	 * This ensures that no buffer is active for subsequent OpenGL operations.
	 */
	void Unbind() const;
};
