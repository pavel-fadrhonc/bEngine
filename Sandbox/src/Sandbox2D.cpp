#include "Sandbox2D.h"

#include "imgui.h"
#include "bEngine/Renderer/RenderCommand.h"
#include "bEngine/Renderer/Renderer.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
     m_CameraController(16.0f / 9.0f, 1.0, 90, true)
{}

void Sandbox2D::OnAttach()
{
    float verticesSq[3 * 4] = {
        -0.5f, -0.5f, 0.0f,     
         0.5f, -0.5f, 0.0f,     
         0.5f,  0.5f, 0.0f,     
        -0.5f,  0.5f, 0.0f 
     };
    ben::Ref<ben::VertexBuffer> squareVertexBuffer;
    squareVertexBuffer.reset(ben::VertexBuffer::Create(verticesSq,sizeof(verticesSq)));
    squareVertexBuffer->SetLayout({
        {ben::ShaderDataType::Float3, "a_Position"}
    });
    m_VertexArray = ben::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(squareVertexBuffer);

    uint32_t indicesSq[6] = {0, 1, 2, 0, 2, 3};
    ben::Ref<bEngine::IndexBuffer> indexBufferSquare;
    indexBufferSquare.reset(ben::IndexBuffer::Create(indicesSq,sizeof(indicesSq)));
    m_VertexArray->SetIndexBuffer(indexBufferSquare);

    m_Shader = ben::Shader::Create("Square", "Assets/Shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
    
}

void Sandbox2D::OnUpdate(bEngine::Timestep dt)
{
    m_CameraController.OnUpdate(dt);

    ben::RenderCommand::SetClearColor( {0.1f,0.1f,0.1f,1 });
    ben::RenderCommand::Clear();
    
    ben::Renderer::BeginScene(m_CameraController.GetCamera());

    auto redColorUniform = bEngine::Float4ShaderUniform{m_Shader, "u_Color", m_SquareColor};
    std::array<bEngine::ShaderUniform*, 1> redColUniform {&redColorUniform};

    auto translation = glm::translate(glm::mat4(1.0), glm::vec3(0,0,0));
    
    bEngine::Renderer::Submit(m_VertexArray, m_Shader, translation, redColUniform);

    bEngine::Renderer::EndScene();
}

void Sandbox2D::OnEvent(bEngine::Event& event)
{
    m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Color Settings");
    ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
    ImGui::End();

}
