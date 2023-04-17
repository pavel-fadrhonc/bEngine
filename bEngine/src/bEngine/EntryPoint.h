#pragma once
#include "../bEngine.h"

#ifdef BE_PLATFORM_WINDOWS

extern bEngine::Application* bEngine::CreateApplication();

int main(int argc, char** argv)
{
    bEngine::Log::Init();
    BE_CORE_WARN("Initialized Log.");
    int var = 5;
    BE_CORE_INFO("Variable value {0}", var);
    
    auto app = bEngine::CreateApplication();
    app->Run();
    delete app;
}

#endif
