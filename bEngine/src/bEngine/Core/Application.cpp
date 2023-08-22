#include "bepch.h"

#include "Application.h"

#include "Log.h"
#include "bEngine/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

#include "bEngine/Renderer/Renderer.h"

namespace bEngine
{
    Application* Application::s_Instance = nullptr;
    
    bEngine::Application::Application() : m_Running(true)
    {
        BE_CORE_ASSERT(!s_Instance, "Application already exists!")
        
        s_Instance = this;
        
        m_Window = std::unique_ptr<Window>{Window::Create()};
        m_Window->SetEventCallback(BE_BIND_EVENT_FUNC(Application::OnEvent));
        m_Window->SetVSync(true);

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer;
        PushOverlay(m_ImGuiLayer);
    }

    bEngine::Application::~Application()
    {
        m_ImGuiLayer->OnDetach();
    }

    void bEngine::Application::Run()
    {
        while (m_Running)
        {
            // TODO: MOVE THIS TO SANDBOX
            //Renderer::Flush();

            auto dt = m_Timer.SampleDeltaTime();

            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(dt);
            }
            
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;   
    }

    bool Application::OnWindowsResize(WindowResizeEvent& event)
    {
        if (event.GetWidth() == 0 || event.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        
        m_Minimized = false;
        Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

        return false;
    }

    void bEngine::Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher{e};
        dispatcher.Dispatch<WindowCloseEvent>(BE_BIND_EVENT_FUNC(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BE_BIND_EVENT_FUNC(Application::OnWindowsResize));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled())
                break;
        }
        
        //BE_CORE_TRACE("{0}", e.ToString());
    }


}
