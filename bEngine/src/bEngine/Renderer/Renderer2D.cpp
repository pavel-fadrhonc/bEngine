#include "bepch.h"
#include "Renderer2D.h"

#include "Buffer.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace bEngine
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        // TODO: texid
    };
    
    struct Renderer2DData
    {
        // max number of entities for given draw call (batch)
        constexpr static int MAX_QUADS = 10'000;
        constexpr static int MAX_VERTICES = 4 * MAX_QUADS;
        constexpr static int MAX_INDICES = 6 * MAX_QUADS;
        
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;

        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
    };

    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {
        BE_PROFILE_FUNCTION();

        s_Data.QuadVertexBuffer = (VertexBuffer::Create(s_Data.MAX_VERTICES * sizeof(QuadVertex)));
        s_Data.QuadVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Tint"},
            {ShaderDataType::Float2, "a_TextCoord"}
        });
        s_Data.QuadVertexArray = VertexArray::Create();
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MAX_VERTICES];

        uint32_t* quadIndices = new uint32_t[s_Data.MAX_INDICES];

        uint32_t offset = 0;
        for (int i = 0; i < s_Data.MAX_INDICES; i+=6, offset += 4)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 0;
            quadIndices[i + 4] = offset + 2;
            quadIndices[i + 5] = offset + 3;
        }
        
        Ref<bEngine::IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices,s_Data.MAX_INDICES);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

        delete[] quadIndices;
        
        s_Data.TextureShader = Shader::Create("Texture", "Assets/Shaders/Texture.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetInt("u_Texture", 0);

        s_Data.WhiteTexture = Texture2D::Create(1,1);
        static uint32_t data = UINT32_MAX;
        s_Data.WhiteTexture->SetData(&data, sizeof(data));
    }

    void Renderer2D::Shutdown()
    {
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        BE_PROFILE_FUNCTION();
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::EndScene()
    {
        BE_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*) s_Data.QuadVertexBufferPtr - (uint8_t*) s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
        
        Flush();
    }

    void Renderer2D::Flush()
    {
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }

    void Renderer2D::DrawQuadRotated(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuadRotated(glm::vec3(position, 1.0), rotation, size, color);
    }

    void Renderer2D::DrawQuadRotated(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        BE_PROFILE_FUNCTION();
        s_Data.TextureShader->Bind(); // bind the shader just in case it was rebound
        s_Data.WhiteTexture->Bind();
        
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
            glm::rotate(glm::mat4(1.0), glm::radians(rotation), {0,0,1}) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data.TextureShader->SetFloat4("u_Color", color);
        s_Data.TextureShader->SetMat4("u_Model", transform);

        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
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
        s_Data.TextureShader->Bind();
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
        glm::rotate(glm::mat4(1.0), glm::radians(rotation), {0,0,1}) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data.TextureShader->SetMat4("u_Model", transform);
        s_Data.TextureShader->SetFloat4("u_Color", textureShaderProperties.Color);
        s_Data.TextureShader->SetFloat2("u_Tiling", textureShaderProperties.Tiling);
        s_Data.TextureShader->SetFloat2("u_Offset", textureShaderProperties.Offset);
        
        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(glm::vec3(position, 1.0), size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        BE_PROFILE_FUNCTION();

        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {0.0, 0.0};
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {1.0, 0.0};
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {1.0, 1.0};
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {0.0, 1.0};
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount+=6;
        
        //s_Data.TextureShader->Bind(); // bind the shader just in case it was rebound
        //s_Data.WhiteTexture->Bind();
        
        // auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
        // glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        //
        // s_Data.TextureShader->SetFloat4("u_Color", color);
        // s_Data.TextureShader->SetMat4("u_Model", transform);
        //
        // s_Data.VertexArray->Bind();
        // RenderCommand::DrawIndexed(s_Data.VertexArray);
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
        s_Data.TextureShader->Bind();
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data.TextureShader->SetMat4("u_Model", transform);
        s_Data.TextureShader->SetFloat4("u_Color", textureShaderProperties.Color);
        s_Data.TextureShader->SetFloat2("u_Tiling", textureShaderProperties.Tiling);
        s_Data.TextureShader->SetFloat2("u_Offset", textureShaderProperties.Offset);
        
        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }
}


