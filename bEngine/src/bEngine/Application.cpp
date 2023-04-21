#include "bepch.h"

#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

bEngine::Application::Application() : m_Running(true)
{
    m_Window = std::unique_ptr<Window>{Window::Create()};
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
        
        m_Window->OnUpdate();
    }
}
