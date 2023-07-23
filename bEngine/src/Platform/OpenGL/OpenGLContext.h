#pragma once
#include "bEngine/Renderer/GraphicsContext.h"
#include "Platform/Windows/WindowsWindow.h"

struct GLFWwindow;

namespace bEngine
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
        {
            BE_CORE_ASSERT(windowHandle, "Window handle is null!");
        }
        
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}

