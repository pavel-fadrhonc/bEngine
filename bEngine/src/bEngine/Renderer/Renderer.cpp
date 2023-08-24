#include "bepch.h"
#include "Renderer.h"

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Renderer2D.h"
#include "ShaderUniform.h"

namespace bEngine
{
    OrthographicCamera* Renderer::m_Camera = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0,0,width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_Camera = &camera;        
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const bEngine::Ref<VertexArray>& vertexArray, const bEngine::Ref<Shader>& shader,
        const glm::mat4& transform, std::span<Ref<ShaderUniform>> uniforms)
    {
        shader->Bind();

        shader->SetMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
        shader->SetMat4("u_Model", transform);

        for(const auto& uniform : uniforms)
        {
            uniform->SetUniform();
        }
        
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}
