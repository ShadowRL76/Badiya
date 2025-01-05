#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// Represents a vertex buffer used in OpenGL for storing vertex data.
/// </summary>
class VertexBuffer
{
private:
	/// <summary>
	/// The renderer ID for the vertex buffer.
	/// </summary>
	unsigned int m_RendererID;

public:
	/// <summary>
	/// Constructor that creates a VertexBuffer from the provided vertex data.
	/// Initializes the buffer and stores the vertex data in OpenGL.
	/// </summary>
	/// <param name="data">Pointer to the vertex data array.</param>
	/// <param name="size">The size of the vertex data in bytes.</param>
	VertexBuffer(const void* p_data, unsigned int size);

	/// <summary>
	/// Destructor that cleans up the vertex buffer resources.
	/// </summary>
	~VertexBuffer();

	/// <summary>
	/// Binds the vertex buffer for use in OpenGL.
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds the vertex buffer, making it no longer active in OpenGL.
	/// </summary>
	void Unbind() const;
};

#endif
