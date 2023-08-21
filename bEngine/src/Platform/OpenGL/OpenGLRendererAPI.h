#pragma once
#include "bEngine/Renderer/RendererAPI.h"

namespace bEngine
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void DrawIndexed(const bEngine::Ref<VertexArray>& vertexArray) override;
        void Init() override;
    };
}

