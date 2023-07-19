#include "bepch.h"

#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

#include "Input.h"
#include "glad/glad.h"

namespace bEngine
{
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;
    
    bEngine::Application::Application() : m_Running(true)
    {
        BE_CORE_ASSERT(!s_Instance, "Application already exists!");
        
        s_Instance = this;
        
        m_Window = std::unique_ptr<Window>{Window::Create()};
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
    }

    bEngine::Application::~Application()
    {
    }

    void bEngine::Application::Run()
    {
        // WindowResizeEvent e(1200, 720);
        //
        // if (e.IsInCategory(EventCategoryApplication))
        // {
        //     BE_CORE_TRACE(e.ToString());        
        // }
        // if (e.IsInCategory(EventCategoryInput))
        // {
        //     BE_CORE_TRACE(e.ToString());
        // }
        //

        while (m_Running)
        {
            glClearColor(1,0,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            auto[x,y] = Input::GetMousePosition();

            //BE_CORE_TRACE("{0}, {1}", x, y);
            
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

    void bEngine::Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher{e};
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled())
                break;
        }
        
        //BE_CORE_TRACE("{0}", e.ToString());
    }


}
