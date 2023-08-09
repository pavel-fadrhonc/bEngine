﻿#include "bepch.h"

#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

#include "Input.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

namespace bEngine
{
    #define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;
    
    bEngine::Application::Application() : m_Running(true),
        m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        BE_CORE_ASSERT(!s_Instance, "Application already exists!")
        
        s_Instance = this;
        
        m_Window = std::unique_ptr<Window>{Window::Create()};
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

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
            
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

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
