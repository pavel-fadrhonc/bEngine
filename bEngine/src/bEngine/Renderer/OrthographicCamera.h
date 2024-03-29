﻿#pragma once

#include "glm/gtc/type_ptr.hpp"
#include "bEngine/Core/Core.h"

namespace bEngine
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top)
            : m_Position({0,0,0}), m_Rotation(0.0f),
        m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
        {
            BE_CORE_ASSERT(left < right && bottom < top, "Orthographic camera frustum is invalid!")
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }

        void SetProjection(float left, float right, float bottom, float top);
        
        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

        float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        void RecalculateViewMatrix();
        void RecalculateViewProjectionMatrix();

    private:
        glm::vec3 m_Position;
        float m_Rotation;

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}

