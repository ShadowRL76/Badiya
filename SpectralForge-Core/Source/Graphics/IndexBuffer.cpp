#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* p_data, const unsigned int count)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), p_data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
	delete[] arr;
}

int* IndexBuffer::Cube()
{
	arr = new int[] {
		0, 1, 2,   // Triangle 1
			3, 4, 5,   // Triangle 2
			6, 7, 8,   // Triangle 3
			9, 10, 11, // Triangle 4
			12, 13, 14,// Triangle 5
			15, 16, 17,// Triangle 6
			18, 19, 20,// Triangle 7
			21, 22, 23,// Triangle 8
			24, 25, 26,// Triangle 9
			27, 28, 29,// Triangle 10
			30, 31, 32,// Triangle 11
			33, 34, 35, // Triangle 12
			-5
		};

	return arr;
}

int IndexBuffer::GetCubeSize()
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

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}