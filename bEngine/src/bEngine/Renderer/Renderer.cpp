#include "bepch.h"
#include "Renderer.h"

#include "OrthographicCamera.h"
#include "RenderCommand.h"

namespace bEngine
{
    OrthographicCamera* Renderer::m_Camera = nullptr;
    
    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_Camera = &camera;        
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader,
        const glm::mat4& transform)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
        shader->UploadUniformMat4("u_Model", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}
