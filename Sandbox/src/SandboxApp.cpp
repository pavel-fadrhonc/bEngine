#include <bEngine.h>

#include <iostream>

class ExampleLayer : public bEngine::Layer
{
public:
    ExampleLayer()  
        :Layer("Example"){}

    void OnUpdate() override
    {
        BE_INFO("Example layer updated.");
    }
    void OnEvent(bEngine::Event& event) override
    {
        BE_TRACE("{0}", event.ToString());
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
