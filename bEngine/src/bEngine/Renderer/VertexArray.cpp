#include "bepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace bEngine
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::None: return Ref<VertexArray>{new VoidVertexArray()};
            case RendererAPI::APIType::OpenGL: return Ref<VertexArray>{new OpenGLVertexArray()}; 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }
}
