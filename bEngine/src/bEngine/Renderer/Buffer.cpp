#include "bepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace bEngine
{
    Ref<VertexBuffer> VertexBuffer::Create(size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::None: return CreateRef<VoidVertexBuffer>();
            case RendererAPI::APIType::OpenGL: return CreateRef<OpenGLVertexBuffer>(size); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;   
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::None: return CreateRef<VoidVertexBuffer>();
            case RendererAPI::APIType::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, size_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::None: return CreateRef<VoidIndexBuffer>();
            case RendererAPI::APIType::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }

    
}
