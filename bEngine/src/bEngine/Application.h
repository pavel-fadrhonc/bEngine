#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/OrthographicCamera.h"

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
        OrthographicCamera& GetCamera() { return m_Camera; }
        
    private:
        bool OnWindowClose(WindowCloseEvent& event);
        
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = false;
        LayerStack m_LayerStack;
        
        static Application* s_Instance;

        OrthographicCamera m_Camera;
    };

    // To be defined in client
    Application* CreateApplication();
}
