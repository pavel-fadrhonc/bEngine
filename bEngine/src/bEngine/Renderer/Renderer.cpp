#include "bepch.h"
#include "Renderer.h"

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "ShaderUniform.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace bEngine
{
    OrthographicCamera* Renderer::m_Camera = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
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
        const glm::mat4& transform, std::span<ShaderUniform*> uniforms)
    {
        shader->Bind();

        auto openglShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
        
        openglShader->UploadUniformMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
        openglShader->UploadUniformMat4("u_Model", transform);

        for(const auto& uniform : uniforms)
        {
            uniform->SetUniform();
        }
        
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}
