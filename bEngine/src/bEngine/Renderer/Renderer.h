#pragma once

#include <span>
#include "OrthographicCamera.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "ShaderUniform.h"

namespace bEngine
{
    class Renderer
    {
    public:
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);
        
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        
        static void Submit(const bEngine::Ref<VertexArray>& vertexArray,
            const bEngine::Ref<Shader>& shader,
            const glm::mat4& transform = glm::mat4(1.0f),
            std::span<ShaderUniform*> uniforms = {});
        
        static RendererAPI::APIType GetAPI() { return RendererAPI::GetAPI(); }

    private:
        static OrthographicCamera* m_Camera;
    };
}

