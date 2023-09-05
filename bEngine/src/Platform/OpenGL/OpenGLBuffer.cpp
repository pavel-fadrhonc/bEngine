#include "bepch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

////////////////////////////////////////////////////////////////////////////
/// VERTEX BUFFER
////////////////////////////////////////////////////////////////////////////

bEngine::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
{
    BE_PROFILE_FUNCTION();
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

bEngine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    BE_PROFILE_FUNCTION();
    glDeleteBuffers(1, &m_RendererID);
}

void bEngine::OpenGLVertexBuffer::Bind() const
{
    BE_PROFILE_FUNCTION();
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void bEngine::OpenGLVertexBuffer::Unbind() const
{
    BE_PROFILE_FUNCTION();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

////////////////////////////////////////////////////////////////////////////
/// INDEX BUFFER
////////////////////////////////////////////////////////////////////////////

bEngine::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
}

bEngine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void bEngine::OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void bEngine::OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
