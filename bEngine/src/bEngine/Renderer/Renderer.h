#pragma once
#include "OrthographicCamera.h"
#include "RendererAPI.h"
#include "Shader.h"

namespace bEngine
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray,
            const std::shared_ptr<Shader>& shader,
            const glm::mat4& transform = glm::mat4(1.0f));
        
        static RendererAPI::APIType GetAPI() { return RendererAPI::GetAPI(); }

    private:
        static OrthographicCamera* m_Camera;
    };
}

