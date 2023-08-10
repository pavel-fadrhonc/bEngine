﻿#include "bepch.h"

#include "Timer.h"

#include "GLFW/glfw3.h"

namespace bEngine
{
    Timestep Timer::SampleDeltaTime()
    {
        auto now = glfwGetTime(); // this should be platform independent
        auto delta = now - m_LastDeltaPoint;
        m_LastDeltaPoint = now;
        return static_cast<float>(delta);
    }
}

