#include "bepch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace bEngine
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::None:      return GL_FLOAT;
            case ShaderDataType::Float:     return GL_FLOAT;
            case ShaderDataType::Float2:    return GL_FLOAT;
            case ShaderDataType::Float3:    return GL_FLOAT;
            case ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderDataType::Mat3:      return GL_FLOAT;
            case ShaderDataType::Mat4:      return GL_FLOAT;
            case ShaderDataType::Int:       return GL_INT;
            case ShaderDataType::Int2:      return GL_INT;
            case ShaderDataType::Int3:      return GL_INT;
            case ShaderDataType::Int4:      return GL_INT;
            case ShaderDataType::Bool:      return GL_BOOL;
        }

        BE_CORE_ASSERT(false, "Unknown shader data type.");
        return 0;
    }
    
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
    {
        BE_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");
        
        glBindVertexArray(m_RendererID);
        buffer->Bind();

        int i = 0;
        const auto& layout = buffer->GetLayout();
        for (const auto& elem : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, elem.GetElementCount(),
                ShaderDataTypeToOpenGLBaseType(elem.Type),
                elem.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void *) elem.Offset);

            ++i;
        }

        m_VertexBuffers.push_back(buffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
    {
        glBindVertexArray(m_RendererID);
        buffer->Bind();

        m_IndexBuffer = buffer;
    }
}
