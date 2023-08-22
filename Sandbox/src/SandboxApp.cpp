#include <bEngine.h>

#include "bEngine/Renderer/Texture.h"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public bEngine::Layer
{
public:
    ExampleLayer()  
        :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        using VertexArray = bEngine::VertexArray;
        using VertexBuffer = bEngine::VertexBuffer;
        using IndexBuffer = bEngine::IndexBuffer;
        using BufferLayout = bEngine::BufferLayout;
        using ShaderDataType = bEngine::ShaderDataType;
        using Shader = bEngine::Shader;
        
        m_TriangleVertexArray = VertexArray::Create();
        
        float vertices[3 * 7] = {
           -0.5f, -0.5f, 0.0f,      0.8f, 0.0f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 0.8f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f,       0.8f, 0.8f, 0.2f, 1.0f,
        };
        
        bEngine::Ref<VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
        
        BufferLayout bufferLayout {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };

        triangleVertexBuffer->SetLayout(bufferLayout);
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        bEngine::Ref<IndexBuffer> indexBufferTriangle;
        indexBufferTriangle.reset(IndexBuffer::Create(indices,sizeof(indices)));
        m_TriangleVertexArray->SetIndexBuffer(indexBufferTriangle);

        m_SquareVertexArray = VertexArray::Create();

        float verticesSq[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0, 0.0,     
             0.5f, -0.5f, 0.0f, 1.0, 0.0,     
             0.5f,  0.5f, 0.0f, 1.0, 1.0,     
            -0.5f,  0.5f, 0.0f, 0.0, 1.0 
         };

        bEngine::Ref<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(VertexBuffer::Create(verticesSq,sizeof(verticesSq)));
        
        squareVertexBuffer->SetLayout({
                {ShaderDataType::Float3, "a_Position"},
              { ShaderDataType::Float2, "a_TexCoord"}          
            });

        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t indicesSq[6] = {0, 1, 2, 0, 2, 3};
        bEngine::Ref<IndexBuffer> indexBufferSquare;
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
        
        m_ShaderTriangle = Shader::Create("Triangle", vertexSourceTriangle, fragmentSourceTriangle);

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
            uniform vec3 u_Color;
                       
            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_ShaderSquare = Shader::Create("Square", vertexSourceSquare, fragmentSourceSquare);
        
        std::string vertexSourceTextured = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position; 
            layout(location = 1) in vec2 a_TextCoord; 

            out vec3 v_Position;
            out vec2 v_TextCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Model;
                       
            void main()
            {
                gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
                v_Position = a_Position;
                v_TextCoord = a_TextCoord;
            }
        )";


        std::string fragmentSourceTextured = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position; 
            in vec2 v_TextCoord;
 
            uniform sampler2D u_Texture;
                       
            void main()
            {
                //color = vec4(v_TextCoord, 0.0, 1.0);
                color = texture(u_Texture, v_TextCoord);
            }
        )";

        m_Texture = bEngine::Texture2D::Create("Assets/Textures/TextTest1.png");

        m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

        //m_ShaderTextured.reset(Shader::Create(vertexSourceTextured, fragmentSourceTextured));
    }

    void OnUpdate(bEngine::Timestep dt) override
    {
        //BE_TRACE("Delta time {0}s ({1}ms)", dt.GetSeconds(), dt.GetMilliseconds());

        bEngine::RenderCommand::SetClearColor( {0.1f,0.1f,0.1f,1 });
        bEngine::RenderCommand::Clear();
        
        //camera.SetRotation(45);
        bEngine::Renderer::BeginScene(m_Camera);

        static glm::vec2 translation = {0.0f, 0.0f};
        if (bEngine::Input::IsKeyPressed(BE_KEY_LEFT))
            translation.x -= m_ObjectMoveSpeed * dt;
        if (bEngine::Input::IsKeyPressed(BE_KEY_RIGHT))
            translation.x += m_ObjectMoveSpeed * dt;
        if (bEngine::Input::IsKeyPressed(BE_KEY_DOWN))
            translation.y -= m_ObjectMoveSpeed * dt;
        if (bEngine::Input::IsKeyPressed(BE_KEY_UP))
            translation.y += m_ObjectMoveSpeed * dt;
        
        if (bEngine::Input::IsKeyPressed(BE_KEY_A))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-m_CameraMoveSpeed * dt, 0.0f, 0.0f));
        }
        if (bEngine::Input::IsKeyPressed(BE_KEY_D))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(m_CameraMoveSpeed * dt, 0.0f, 0.0f));
        }
        if (bEngine::Input::IsKeyPressed(BE_KEY_W))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed * dt, 0.0f));
        }
        if (bEngine::Input::IsKeyPressed(BE_KEY_S))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, -m_CameraMoveSpeed * dt, 0.0f));
        }
        if (bEngine::Input::IsKeyPressed(BE_KEY_Q))
        {
            m_Camera.SetRotation(m_Camera.GetRotation() - m_CameraRotationSpeed * dt);
        }
        if (bEngine::Input::IsKeyPressed(BE_KEY_E))
        {
            m_Camera.SetRotation(m_Camera.GetRotation() + m_CameraRotationSpeed * dt);
        }

        constexpr auto gridSize = std::pair{10,10};
        constexpr float tileSize = 0.1f;
        const auto scale = glm::scale(glm::mat4(1.0f), glm::vec3{tileSize});

        auto redColorUniform = bEngine::Float3ShaderUniform{m_ShaderSquare, "u_Color", m_Square1Color};
        auto blueColorUniform = bEngine::Float3ShaderUniform{m_ShaderSquare, "u_Color", m_Square2Color};
        
        std::array<bEngine::ShaderUniform*, 1> redColUniform {&redColorUniform};
        std::array<bEngine::ShaderUniform*, 1> blueColUniform {&blueColorUniform};

        m_ShaderSquare->Bind();
        
        for (int x = 0; x < gridSize.first; x++)
        {
            for (int y = 0; y < gridSize.second; y++)
            {
                constexpr float tileMargin = 0.01f;
                constexpr auto tileOffset = (tileSize + tileMargin);
                
                glm::vec3 pos(x * tileOffset + translation.x, y * tileOffset + translation.y, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                if ((x+y) % 2 == 0)
                    bEngine::Renderer::Submit(m_SquareVertexArray, m_ShaderSquare, transform, redColUniform);
                else
                    bEngine::Renderer::Submit(m_SquareVertexArray, m_ShaderSquare, transform, blueColUniform);
            }
        }

        auto textureShader = m_ShaderLibrary.Get("Texture");
        
        m_Texture->Bind();
        textureShader->Bind();
        auto textureUniform = bEngine::IntShaderUniform{textureShader, "u_Texture", 0};
        std::array<bEngine::ShaderUniform*, 1> textureUniformArray {&textureUniform};
        bEngine::Renderer::Submit(m_SquareVertexArray, textureShader, glm::mat4{1.0}, textureUniformArray);
        
//        bEngine::Renderer::Submit(m_SquareVertexArray, m_ShaderSquare, T_square * R_square * S_square);
        //bEngine::Renderer::Submit(m_TriangleVertexArray, m_ShaderTriangle, glm::mat4(1.0f));
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
        ImGui::Begin("Color Settings");
        ImGui::ColorEdit3("Square 1 color", glm::value_ptr(m_Square1Color));
        ImGui::ColorEdit3("Square 2 color", glm::value_ptr(m_Square2Color));
        ImGui::End();
    }

private:
    bEngine::Ref<bEngine::Shader> m_ShaderTriangle;
    bEngine::Ref<bEngine::VertexArray> m_TriangleVertexArray;
    bEngine::Ref<bEngine::Shader> m_ShaderSquare;
    bEngine::Ref<bEngine::VertexArray> m_SquareVertexArray;
    
    //bEngine::Ref<bEngine::Shader> m_ShaderTextured;
    bEngine::Ref<bEngine::Texture2D> m_Texture;

    bEngine::OrthographicCamera m_Camera;

    bEngine::ShaderLibrary m_ShaderLibrary;

    float m_CameraMoveSpeed = 0.5f;
    float m_CameraRotationSpeed = 180;
    float m_ObjectMoveSpeed = 10;

    glm::vec3 m_Square1Color = {0.85f, 0.15f, 0.15f};
    glm::vec3 m_Square2Color = {0.15f, 0.15f, 0.85f};
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
