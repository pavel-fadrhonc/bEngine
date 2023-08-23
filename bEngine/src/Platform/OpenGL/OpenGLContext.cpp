#include "bepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#ifdef BE_ENABLE_ASSERTS
    int versionMajor;
    int versionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

    BE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "bEngine requires at least OpenGL version 4.5!");
#endif

namespace bEngine
{
    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        BE_CORE_ASSERT(status, "Failed to initialize Glad.");

        BE_CORE_INFO("OpenGL info:");
        BE_CORE_INFO("  Vendor: {}", (char *) glGetString(GL_VENDOR));
        BE_CORE_INFO("  Renderer: {}", (char *) glGetString(GL_RENDERER));
        BE_CORE_INFO("  Version: {}", (char *) glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glBegin(GL_TRIANGLES);

        glEnd();
        
        glfwSwapBuffers(m_WindowHandle);
    }
}
