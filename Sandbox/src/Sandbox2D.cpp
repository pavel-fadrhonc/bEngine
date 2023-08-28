#include "Sandbox2D.h"

#include "imgui.h"
#include "bEngine///timer.h"
#include "bEngine/Renderer/RenderCommand.h"
#include "bEngine/Renderer/Renderer.h"
#include "bEngine/Renderer/Renderer2D.h"
#include "glm/gtc/type_ptr.hpp"

#define PROFILE_SCOPE(name) bEngine::Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult);})

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
     m_CameraController(16.0f / 9.0f, 1.0, 90, true)
{}

void Sandbox2D::OnAttach()
{
    m_quadTexture = bEngine::Texture2D::Create("Assets/Textures/TextTest1.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(bEngine::Timestep dt)
{
    //ben::Timer timer("Sandbox2D::OnUpdate", [&](auto profileResult) { m_ProfileResults.push_back(profileResult);});

    PROFILE_SCOPE("Sandbox2D::OnUpdate");

    {
        PROFILE_SCOPE("Sandbox2D::Camera update");
        m_CameraController.OnUpdate(dt);
    }

    {
        PROFILE_SCOPE("Sandbox2D::Render init");
        ben::RenderCommand::SetClearColor( {0.1f,0.1f,0.1f,1 });
        ben::RenderCommand::Clear();
    }

    {
        PROFILE_SCOPE("Sandbox2D::Draw calls");
        ben::Renderer2D::BeginScene(m_CameraController.GetCamera());

        //ben::Renderer2D::DrawQuad({0.0, 0.0}, 0.0, {1.0, 1.0}, {0.8, 0.2, 0.3, 1.0}, m_quadTexture);
        ben::Renderer2D::DrawQuad({0.0, 0.0}, 0.0, {1.0, 1.0}, {0.8, 0.2, 0.3, 1.0});
        //ben::Renderer2D::DrawQuad({1.0, -0.5}, 30.0, {0.5, 3.0}, {1.0,1.0,1.0,1.0});
        ben::Renderer2D::DrawQuad({1.0, -0.5}, 30.0, {0.5, 3.0}, {1.0,1.0,1.0,1.0}, m_quadTexture);
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

    for (auto result : m_ProfileResults)
    {
        // std::stringstream ss;
        // ss << result.name << " " << result.time << '\n';

        char label[50];
        strcpy(label, " %.3fms");
        strcat(label, result.name);

        ImGui::Text(label, result.time);

        m_ProfileResults.clear();
    }

}
