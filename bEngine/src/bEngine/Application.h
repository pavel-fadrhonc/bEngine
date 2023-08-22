#pragma once

#include <stdbool.h>

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Core/Timer.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"

namespace bEngine
{
    class BENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        static inline Application& Get() {return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window;}
        
    private:
        bool OnWindowClose(WindowCloseEvent& event);
        bool OnWindowsResize(WindowResizeEvent& event);
        
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = false;
        LayerStack m_LayerStack;
        Timer m_Timer;
        bool m_Minimized = false;

        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();
}
