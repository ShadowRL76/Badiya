#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* p_data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, p_data, GL_STATIC_DRAW); 
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);

}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
