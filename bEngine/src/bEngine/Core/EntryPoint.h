#pragma once

#ifdef BE_PLATFORM_WINDOWS

#include "bEngine/Debug/Instrumentor.h"

extern bEngine::Application* bEngine::CreateApplication();

int main(int argc, char** argv)
{
    bEngine::Log::Init();

    BE_PROFILE_BEGIN_SESSION("Startup", "bEngineProfile-Startup.json");
    auto app = bEngine::CreateApplication();
    BE_PROFILE_END_SESSION();
    
    BE_PROFILE_BEGIN_SESSION("Runtime", "bEngineProfile-Runtime.json");
    app->Run();
    BE_PROFILE_END_SESSION();
    
    BE_PROFILE_BEGIN_SESSION("Shutdown", "bEngineProfile-Shutdown.json");
    delete app;
    BE_PROFILE_END_SESSION();
}

#endif
