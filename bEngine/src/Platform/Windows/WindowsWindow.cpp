#include "bepch.h"
#include "WindowsWindow.h"

#include "bEngine/Log.h"
#include "bEngine/Events/ApplicationEvent.h"
#include "bEngine/Events/KeyEvent.h"
#include "bEngine/Events/MouseEvent.h"

namespace bEngine
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error_code, const char* description)
    {
        BE_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
    }
    
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }
    
    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        BE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            // TODO: glfwTerminate on shutdown
            int success = glfwInit();
            BE_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int) props.Width, (int) props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            data.Width = width;
            data.Height = height;
            auto e = WindowResizeEvent(width, height);
            data.EventCallback(e);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            auto e = WindowCloseEvent();
            data.EventCallback(e);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                    {
                        auto event = KeyPressedEvent(key, 0);
                        data.EventCallback(event);
                        break;
                    }
                case GLFW_REPEAT:
                    {
                        auto event = KeyPressedEvent(key, 1);
                        data.EventCallback(event);
                        break;
                    }
                case GLFW_RELEASE:
                    {
                        auto event = KeyReleasedEvent(key);
                        data.EventCallback(event);
                        break;
                    }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                    {
                        auto e =  MouseButtonPressedEvent(button);
                        data.EventCallback(reinterpret_cast<Event&>(e));
                        break;
                    }
                case GLFW_RELEASE:
                    {
                        auto ev = MouseButtonReleasedEvent(button);
                        data.EventCallback(reinterpret_cast<Event&>(ev));
                        break;
                    }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            auto event = MouseScrolledEvent(static_cast<float>(xoffset), static_cast<float>(yoffset));
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            auto event = MouseMovedEvent(static_cast<float>(xpos), static_cast<float>(ypos));
            data.EventCallback(event);
        });
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }
}
