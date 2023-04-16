#pragma once
#include "../bEngine.h"

#ifdef BE_PLATFORM_WINDOWS

extern bEngine::Application* bEngine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = bEngine::CreateApplication();
    app->Run();
    delete app;
}

#endif
