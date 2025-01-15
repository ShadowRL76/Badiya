#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* p_data, const unsigned long long size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, p_data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
	delete[] arr;
}

float* VertexBuffer::Cube()
{
	arr = new float[]
		{
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,

                // Front face
                -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

                // Left face
                -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                -1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
                -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

                // Right face
                1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

                // Bottom face
                -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
                -1.0f, -1.0f, -1.0f, 0.0f, 1.0f,

                // Top face
                -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -5
		};

	return arr;
}

int VertexBuffer::GetCubeSize()
{
	arr = Cube();
	int size{};

	while (*arr != -5)
	{
		size++;
		arr++;
	}

	return size;
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}