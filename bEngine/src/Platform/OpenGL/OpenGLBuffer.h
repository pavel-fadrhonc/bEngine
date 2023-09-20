#pragma once
#include "bEngine/Renderer/Buffer.h"

namespace bEngine
{
    ////////////////////////////////////////////////////////////////////////////
    /// VERTEX BUFFER
    ////////////////////////////////////////////////////////////////////////////
    
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, size_t size);
        OpenGLVertexBuffer(size_t size);
        
        virtual ~OpenGLVertexBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetLayout(const BufferLayout& layout) override { m_BufferLayout = layout; }
        virtual const BufferLayout& GetLayout() const override { return m_BufferLayout;}
        virtual void SetData(const void* data, uint32_t size);

    private:
        uint32_t m_RendererID;
        unsigned int m_VertexBuffer;
        BufferLayout m_BufferLayout; 
    };

    ////////////////////////////////////////////////////////////////////////////
    /// INDEX BUFFER
    ////////////////////////////////////////////////////////////////////////////
    
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        
        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}

