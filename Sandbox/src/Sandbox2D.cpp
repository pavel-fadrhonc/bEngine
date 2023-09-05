#include "Sandbox2D.h"

#include "imgui.h"
#include "bEngine/Debug/Instrumentor.h"
#include "bEngine/Renderer/RenderCommand.h"
#include "bEngine/Renderer/Renderer.h"
#include "bEngine/Renderer/Renderer2D.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
     m_CameraController(16.0f / 9.0f, 1.0, 90, true)
{}

void Sandbox2D::OnAttach()
{
    BE_PROFILE_FUNCTION();
    m_quadTexture = bEngine::Texture2D::Create("Assets/Textures/TextTest1.png");
    m_checkerBoardTexture = bEngine::Texture2D::Create("Assets/Textures/Checkerboard_pattern.png");
}

void Sandbox2D::OnDetach()
{
    BE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(bEngine::Timestep dt)
{
    //ben::Timer timer("Sandbox2D::OnUpdate", [&](auto profileResult) { m_ProfileResults.push_back(profileResult);});

    BE_PROFILE_FUNCTION();
    
    {   
        BE_PROFILE_SCOPE("Sandbox2D::Camera update");
        m_CameraController.OnUpdate(dt);
    }

    {
        BE_PROFILE_SCOPE("Sandbox2D::Render init");
        ben::RenderCommand::SetClearColor( {0.1f,0.1f,0.1f,1 });
        ben::RenderCommand::Clear();
    }

    {
        BE_PROFILE_SCOPE("Sandbox2D::Draw calls");
        ben::Renderer2D::BeginScene(m_CameraController.GetCamera());

        //ben::Renderer2D::DrawQuad({0.0, 0.0}, 0.0, {1.0, 1.0}, {0.8, 0.2, 0.3, 1.0}, m_quadTexture);
        ben::Renderer2D::DrawQuad({0.0, 0.0, -0.9}, {10, 10}, m_checkerBoardTexture,
            {{3.0, 3.0}, {0.5, 0.5}, {1.0,1.0,1.0,1.0}});
        ben::Renderer2D::DrawQuad({0.0, 0.0, 0.5},{1.0, 1.0}, {0.8, 0.2, 0.3, 1.0});
        //ben::Renderer2D::DrawQuad({1.0, -0.5}, 30.0, {0.5, 3.0}, {1.0,1.0,1.0,1.0});
        ben::Renderer2D::DrawQuadRotated({1.0, -0., 0}, 30.0, {0.5, 3.0}, m_quadTexture);
        bEngine::Renderer2D::EndScene();
    }
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
