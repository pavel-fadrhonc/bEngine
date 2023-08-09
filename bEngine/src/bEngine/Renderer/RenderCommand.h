#pragma once
#include "RendererAPI.h"

namespace bEngine
{
    class RenderCommand
    {
    public:
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear()
        {
            s_RendererAPI->Clear();
        }
        
    private:
        static RendererAPI* s_RendererAPI;
        
    };
}

