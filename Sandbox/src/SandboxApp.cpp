#include <bEngine.h>

#include <iostream>

#include "bEngine/Input.h"

class ExampleLayer : public bEngine::Layer
{
public:
    ExampleLayer()  
        :Layer("Example"){}

    void OnUpdate() override
    {
        //BE_INFO("Example layer updated.");

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
        ImGui::Begin("Test");
        ImGui::Text("Hello");
        ImGui::End();
    }
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
