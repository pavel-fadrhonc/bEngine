#include "bepch.h"
#include "bEngine/OrthographicCameraController.h"

#include "bEngine/Core/Input.h"
#include "bEngine/Core/KeyCodes.h"
#include "bEngine/Core/Core.h"

namespace bEngine
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, float moveSpeed, float rotationSpeed, bool rotate)
        :   m_AspectRatio(aspectRatio),
            m_Rotate(rotate),
            m_CameraTranslationSpeed(moveSpeed),
            m_CameraRotationSpeed(rotationSpeed),
            m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep timestep)
    {
        BE_PROFILE_FUNCTION();
        if (Input::IsKeyPressed(BE_KEY_A))
        {
            m_CameraPosition += glm::vec3(-m_CameraTranslationSpeed * timestep, 0.0f, 0.0f);
        }
        if (Input::IsKeyPressed(BE_KEY_D))
        {
            m_CameraPosition += glm::vec3(m_CameraTranslationSpeed * timestep, 0.0f, 0.0f);
        }
        if (Input::IsKeyPressed(BE_KEY_W))
        {
            m_CameraPosition += glm::vec3(0.0f, m_CameraTranslationSpeed * timestep, 0.0f);
        }
        if (Input::IsKeyPressed(BE_KEY_S))
        {
            m_CameraPosition += glm::vec3(0.0f, -m_CameraTranslationSpeed * timestep, 0.0f);
        }

        if (m_Rotate)
        {
            if (Input::IsKeyPressed(BE_KEY_Q))
            {
                m_CameraRotation -= m_CameraRotationSpeed * timestep;
            }
            if (Input::IsKeyPressed(BE_KEY_E))
            {
                m_CameraRotation += m_CameraRotationSpeed * timestep;
            }

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        BE_PROFILE_FUNCTION();
        EventDispatcher dispatcher{e};

        dispatcher.Dispatch<MouseScrolledEvent>(BE_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BE_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        BE_PROFILE_FUNCTION();
        m_ZoomLevel -= e.GetYOffset() * m_CameraZoomSpeed;
        m_ZoomLevel = std::clamp(m_ZoomLevel, MIN_ZOOM, MAX_ZOOM);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        BE_PROFILE_FUNCTION();
        m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        
        return false;
    }
}

