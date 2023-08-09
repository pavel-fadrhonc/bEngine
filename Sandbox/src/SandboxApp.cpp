#include <bEngine.h>

#include <iostream>

#include "bEngine/Input.h"
#include "bEngine/Renderer/OrthographicCamera.h"
#include "bEngine/Renderer/RenderCommand.h"
#include "bEngine/Renderer/Renderer.h"
#include "bEngine/Renderer/Shader.h"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public bEngine::Layer
{
public:
    ExampleLayer()  
        :Layer("Example")
    {

        using VertexArray = bEngine::VertexArray;
        using VertexBuffer = bEngine::VertexBuffer;
        using IndexBuffer = bEngine::IndexBuffer;
        using BufferLayout = bEngine::BufferLayout;
        using ShaderDataType = bEngine::ShaderDataType;
        using Shader = bEngine::Shader;
        
        m_TriangleVertexArray.reset(VertexArray::Create());
        
        float vertices[3 * 7] = {
           -0.5f, -0.5f, 0.0f,      0.8f, 0.0f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 0.8f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f,       0.8f, 0.8f, 0.2f, 1.0f,
        };
        
        std::shared_ptr<VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
        
        BufferLayout bufferLayout {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };

        triangleVertexBuffer->SetLayout(bufferLayout);
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBufferTriangle;
        indexBufferTriangle.reset(IndexBuffer::Create(indices,sizeof(indices)));
        m_TriangleVertexArray->SetIndexBuffer(indexBufferTriangle);

        m_SquareVertexArray.reset(VertexArray::Create());

        float verticesSq[3 * 4] = {
            -0.75f, -0.75f, 0.0f, 
             0.75f, -0.75f, 0.0f,   
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
         };

        std::shared_ptr<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(VertexBuffer::Create(verticesSq,sizeof(verticesSq)));
        
        squareVertexBuffer->SetLayout({
                {ShaderDataType::Float3, "a_Position"}
            });

        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t indicesSq[6] = {0, 1, 2, 0, 2, 3};
        std::shared_ptr<IndexBuffer> indexBufferSquare;
        indexBufferSquare.reset(IndexBuffer::Create(indicesSq,sizeof(indicesSq)));
        m_SquareVertexArray->SetIndexBuffer(indexBufferSquare);
        
        std::string vertexSourceTriangle = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position; 
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Model;
                       
            void main()
            {
                gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
                v_Position = a_Position;
                v_Color = a_Color;
            }
        )";

        std::string fragmentSourceTriangle = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position; 
            in vec4 v_Color;
                       
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";
        
        m_ShaderTriangle.reset(Shader::Create(vertexSourceTriangle, fragmentSourceTriangle));

        std::string vertexSourceSquare = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position; 

            out vec3 v_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Model;
                       
            void main()
            {
                gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
                v_Position = a_Position;
            }
        )";

        std::string fragmentSourceSquare = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position; 
            in vec4 v_Color;
                       
            void main()
            {
                color = vec4(0.2,0.2,0.8, 1.0);
            }
        )";

        m_ShaderSquare.reset(Shader::Create(vertexSourceSquare, fragmentSourceSquare));
    }

    void OnUpdate() override
    {
        //BE_INFO("Example layer updated.");

        bEngine::RenderCommand::SetClearColor( {0.1f,0.1f,0.1f,1 });
        bEngine::RenderCommand::Clear();

        auto& camera = bEngine::Application::Get().GetCamera();
        //camera.SetRotation(45);
        bEngine::Renderer::BeginScene(camera);

        static glm::vec2 translation = {0.0f, 0.0f};
        if (bEngine::Input::IsKeyPressed(BE_KEY_LEFT))
            translation.x -= 0.01f;
        if (bEngine::Input::IsKeyPressed(BE_KEY_RIGHT))
            translation.x += 0.01f;
        if (bEngine::Input::IsKeyPressed(BE_KEY_DOWN))
            translation.y -= 0.01f;
        if (bEngine::Input::IsKeyPressed(BE_KEY_UP))
            translation.y += 0.01f;
        
        auto T_square = glm::translate(glm::mat4(1.0), {translation.x, translation.y, 0.0f});
        auto R_square = mat4_cast(glm::quat(glm::vec3(0.0f, 0.0f, glm::pi<float>() * 0.25f)));
        auto S_square = glm::scale(glm::mat4(1.0), {1.0f, 1.0f, 1.0f});
        
        bEngine::Renderer::Submit(m_SquareVertexArray, m_ShaderSquare, T_square * R_square * S_square);
        bEngine::Renderer::Submit(m_TriangleVertexArray, m_ShaderTriangle, glm::mat4(1.0f));
        bEngine::Renderer::EndScene();

        if (bEngine::Input::IsKeyPressed(BE_KEY_TAB))
        {
            BE_TRACE("Tab has been pressed");
        }
    }
    void OnEvent(bEngine::Event& event) override
    {
        //BE_TRACE("{0}", event.ToString());
    }

    void OnImGuiRender() override
    {
        // ImGui::Begin("Test");
        // ImGui::Text("Hello");
        // ImGui::End();
    }

private:
    std::shared_ptr<bEngine::Shader> m_ShaderTriangle;
    std::shared_ptr<bEngine::VertexArray> m_TriangleVertexArray;
    
    std::shared_ptr<bEngine::Shader> m_ShaderSquare;
    std::shared_ptr<bEngine::VertexArray> m_SquareVertexArray;

};

class Sandbox : public bEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
        
    }
};

bEngine::Application* bEngine::CreateApplication()
{
    return new Sandbox();
}
