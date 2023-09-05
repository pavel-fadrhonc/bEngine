#include "bepch.h"
#include "Renderer2D.h"

#include "Buffer.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace bEngine
{
    struct Renderer2DData
    {
        Ref<VertexArray> VertexArray;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture; 
    };

    static Renderer2DData* s_Data;

    void Renderer2D::Init()
    {
        BE_PROFILE_FUNCTION();
        s_Data = new Renderer2DData;
        
        float verticesSq[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0, 0.0,    
             0.5f, -0.5f, 0.0f, 1.0, 0.0,    
             0.5f,  0.5f, 0.0f, 1.0, 1.0,    
            -0.5f,  0.5f, 0.0f, 0.0, 1.0 
         };
        Ref<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(VertexBuffer::Create(verticesSq,sizeof(verticesSq)));
        squareVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float2, "a_TextCoord"}
        });
        s_Data->VertexArray = VertexArray::Create();
        s_Data->VertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t indicesSq[6] = {0, 1, 2, 0, 2, 3};
        Ref<bEngine::IndexBuffer> indexBufferSquare;
        indexBufferSquare.reset(IndexBuffer::Create(indicesSq,sizeof(indicesSq)));
        s_Data->VertexArray->SetIndexBuffer(indexBufferSquare);
        
        s_Data->TextureShader = Shader::Create("Texture", "Assets/Shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);

        s_Data->WhiteTexture = Texture2D::Create(1,1);
        static uint32_t data = UINT32_MAX;
        s_Data->WhiteTexture->SetData(&data, sizeof(data));
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        BE_PROFILE_FUNCTION();
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuadRotated(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuadRotated(glm::vec3(position, 1.0), rotation, size, color);
    }

    void Renderer2D::DrawQuadRotated(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        BE_PROFILE_FUNCTION();
        s_Data->TextureShader->Bind(); // bind the shader just in case it was rebound
        s_Data->WhiteTexture->Bind();
        
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
            glm::rotate(glm::mat4(1.0), glm::radians(rotation), {0,0,1}) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data->TextureShader->SetFloat4("u_Color", color);
        s_Data->TextureShader->SetMat4("u_Model", transform);

        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuadRotated(const glm::vec2& position, float rotation, const glm::vec2& size,
        Ref<Texture> texture, TextureShaderProperties textureShaderProperties)
    {
        DrawQuadRotated(glm::vec3(position, 1.0), rotation, size, texture, textureShaderProperties);
    }

    void Renderer2D::DrawQuadRotated(const glm::vec3& position, float rotation, const glm::vec2& size,
        Ref<Texture> texture, TextureShaderProperties textureShaderProperties)
    {
        BE_PROFILE_FUNCTION();
        texture->Bind(0);
        s_Data->TextureShader->Bind();
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
        glm::rotate(glm::mat4(1.0), glm::radians(rotation), {0,0,1}) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data->TextureShader->SetMat4("u_Model", transform);
        s_Data->TextureShader->SetFloat4("u_Color", textureShaderProperties.Color);
        s_Data->TextureShader->SetFloat2("u_Tiling", textureShaderProperties.Tiling);
        s_Data->TextureShader->SetFloat2("u_Offset", textureShaderProperties.Offset);
        
        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(glm::vec3(position, 1.0), size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        BE_PROFILE_FUNCTION();
        s_Data->TextureShader->Bind(); // bind the shader just in case it was rebound
        s_Data->WhiteTexture->Bind();
        
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data->TextureShader->SetFloat4("u_Color", color);
        s_Data->TextureShader->SetMat4("u_Model", transform);

        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
        Ref<Texture> texture, TextureShaderProperties textureShaderProperties)
    {
        DrawQuad(glm::vec3(position, 1.0), size, texture, textureShaderProperties);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
        Ref<Texture> texture, TextureShaderProperties textureShaderProperties)
    {
        BE_PROFILE_FUNCTION();
        texture->Bind(0);
        s_Data->TextureShader->Bind();
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data->TextureShader->SetMat4("u_Model", transform);
        s_Data->TextureShader->SetFloat4("u_Color", textureShaderProperties.Color);
        s_Data->TextureShader->SetFloat2("u_Tiling", textureShaderProperties.Tiling);
        s_Data->TextureShader->SetFloat2("u_Offset", textureShaderProperties.Offset);
        
        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }
}


