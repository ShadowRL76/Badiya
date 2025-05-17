#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * @class IndexBuffer
 * @brief Represents an index buffer in OpenGL, used to store indices for drawing elements.
 */
class IndexBuffer {
private:
	/**
	 * @brief The unique ID assigned by OpenGL to this index buffer.
	 * Used to refer to this specific buffer in OpenGL operations.
	 */
	unsigned int m_RendererID;

	int* arr = nullptr;

	/**
	 * @brief The number of indices stored in this buffer.
	 * Helps manage buffer operations like rendering.
	 */
	unsigned int m_Count;

public:
	IndexBuffer() = default;

	/**
	 * @brief Constructs an IndexBuffer and uploads data to the GPU.
	 * @param p_data Pointer to the array of indices to upload.
	 * @param count The number of indices in the array.
	 * Initializes the index buffer by generating a buffer, binding it, and uploading data.
	 */
	IndexBuffer(const void* p_data, unsigned int count);

	/**
	 * @brief Destructor for IndexBuffer.
	 * Cleans up OpenGL resources associated with the buffer.
	 */
	~IndexBuffer();

	int* Cube();

	/**
	 * @brief Binds the index buffer.
	 * Makes the buffer active for subsequent OpenGL element drawing operations.
	 */
	void Bind() const;

	/**
	 * @brief Unbinds the index buffer.
	 * Deactivates the buffer to prevent unintended use.
	 */
	static void Unbind();

	/**
	 * @brief Gets the total number of indices stored in the buffer.
	 * @return The number of indices in the buffer.
	 */
	[[nodiscard]] unsigned int GetCount() const { return m_Count; }

	int GetCubeSize();
};
