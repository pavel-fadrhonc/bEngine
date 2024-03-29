﻿#include "bepch.h"
#include "OrthographicCamera.h"

#include "glm/gtx/transform.hpp"

namespace bEngine
{
    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        BE_PROFILE_FUNCTION();
        
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        RecalculateViewProjectionMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        BE_PROFILE_FUNCTION();
        
        glm::mat4 transform =
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0,0,1)) *
            glm::translate(glm::mat4(1.0f), m_Position);

        m_ViewMatrix = glm::inverse(transform);
        RecalculateViewProjectionMatrix();
    }

    void OrthographicCamera::RecalculateViewProjectionMatrix()
    {
        BE_PROFILE_FUNCTION();
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
