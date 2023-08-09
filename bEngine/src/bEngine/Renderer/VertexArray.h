#pragma once
#include "Buffer.h"

namespace bEngine
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() { }
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
        virtual void SetIndexBuffer (const std::shared_ptr<IndexBuffer>& buffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create();
    };

    class VoidVertexArray : public VertexArray
    {
        virtual void Bind() const override {}
        virtual void Unbind() const override {}

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override {}
        virtual void SetIndexBuffer (const std::shared_ptr<IndexBuffer>& buffer) override {}

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers;}
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer;}

    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}

