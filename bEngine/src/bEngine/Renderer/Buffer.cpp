#include "bepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace bEngine
{
    VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::None: return new VoidVertexBuffer();
            case RendererAPI::APIType::OpenGL: return new OpenGLVertexBuffer(vertices, size); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::None: return new VoidIndexBuffer();
            case RendererAPI::APIType::OpenGL: return new OpenGLIndexBuffer(indices, size); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }

    
}
