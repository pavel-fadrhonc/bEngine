#include <bEngine.h>

#include <iostream>

class Sandbox : public bEngine::Application
{
public:
    Sandbox()
    {
        
    }

    ~Sandbox()
    {
        
    }
};

bEngine::Application* bEngine::CreateApplication()
{
    return new Sandbox();
}
