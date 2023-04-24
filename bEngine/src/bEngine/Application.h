#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

namespace bEngine
{
    class BENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& event);
        
        std::unique_ptr<Window> m_Window;
        bool m_Running = false;
    };

    // To be defined in client
    Application* CreateApplication();
}