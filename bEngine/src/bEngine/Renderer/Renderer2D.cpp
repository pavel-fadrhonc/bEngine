﻿#include "bepch.h"
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
        Ref<Shader> Shader;
    };

    static Renderer2DData* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderer2DData;
        
        float verticesSq[3 * 4] = {
            -0.5f, -0.5f, 0.0f,     
             0.5f, -0.5f, 0.0f,     
             0.5f,  0.5f, 0.0f,     
            -0.5f,  0.5f, 0.0f 
         };
        Ref<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(VertexBuffer::Create(verticesSq,sizeof(verticesSq)));
        squareVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"}
        });
        s_Data->VertexArray = VertexArray::Create();
        s_Data->VertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t indicesSq[6] = {0, 1, 2, 0, 2, 3};
        Ref<bEngine::IndexBuffer> indexBufferSquare;
        indexBufferSquare.reset(IndexBuffer::Create(indicesSq,sizeof(indicesSq)));
        s_Data->VertexArray->SetIndexBuffer(indexBufferSquare);

        s_Data->Shader = Shader::Create("Square", "Assets/Shaders/FlatColor.glsl");
    }

    void bEngine::Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void bEngine::Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->Shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->Shader)->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void bEngine::Renderer2D::EndScene()
    {
    }

    void bEngine::Renderer2D::DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad(glm::vec3(position, 1.0), rotation, size, color);
    }

    void bEngine::Renderer2D::DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data->Shader->Bind(); // bind the shader just in case it was rebound
        
        auto transform = glm::translate(glm::mat4(1.0), glm::vec3(position)) *
            glm::rotate(glm::mat4(1.0), glm::radians(rotation), {0,0,1});
        glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
        
        s_Data->Shader->SetMat4("u_Model", transform);
        s_Data->Shader->SetFloat4("u_Color", color);

        s_Data->VertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->VertexArray);
    }
}

