#pragma once

#include "bEngine/OrthographicCameraController.h"
#include "bEngine/Core/Layer.h"
#include "bEngine/Renderer/Shader.h"
#include "bEngine/Renderer/Texture.h"
#include "bEngine/Renderer/VertexArray.h"

namespace ben = bEngine;

class Sandbox2D : public bEngine::Layer
{
public:
    
    Sandbox2D();

    void OnAttach() override;
    void OnDetach() override;
    
    void OnUpdate(bEngine::Timestep dt) override;
    void OnEvent(bEngine::Event& event) override;
    void OnImGuiRender() override;
private:
    ben::OrthographicCameraController m_CameraController;

    // TEMP
    ben::Ref<ben::VertexArray> m_VertexArray;
    glm::vec4 m_SquareColor = {0.85f, 0.15f, 0.15f, 1.0f};
    ben::Ref<ben::Shader> m_Shader;

    struct ProfileResult
    {
        const char* name;
        float time;
    };

    std::vector<ProfileResult> m_ProfileResults;

    ben::Ref<bEngine::Texture> m_quadTexture;
};
