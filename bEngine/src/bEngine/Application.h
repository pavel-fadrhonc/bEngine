#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace bEngine
{
    class BENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = false;
    };

    // To be defined in client
    Application* CreateApplication();
}