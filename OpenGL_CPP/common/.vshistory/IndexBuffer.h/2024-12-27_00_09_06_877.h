#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// Represents an index buffer used in OpenGL for storing element indices.
/// </summary>
class IndexBuffer
{
private:
	/// <summary>
	/// The renderer ID for the index buffer.
	/// </summary>
	unsigned int m_RendererID;

	/// <summary>
	/// The number of indices in the index buffer.
	/// </summary>
	unsigned int m_Count;

public:
	/// <summary>
	/// Constructor that creates an IndexBuffer from given data.
	/// Initializes the buffer and stores the count of indices.
	/// </summary>
	/// <param name="data">Pointer to the index data array.</param>
	/// <param name="count">The number of indices in the data array.</param>
	IndexBuffer(const unsigned int* p_data, unsigned int count);

	/// <summary>
	/// Destructor that cleans up the index buffer resources.
	/// </summary>
	~IndexBuffer();

	/// <summary>
	/// Binds the index buffer for use in OpenGL.
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds the index buffer, making it no longer active in OpenGL.
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// Gets the number of indices in the buffer.
	/// </summary>
	/// <returns>The number of indices in the buffer.</returns>
	inline unsigned int GetCount() const { return m_Count; }
};

#endif
