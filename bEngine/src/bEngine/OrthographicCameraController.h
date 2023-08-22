#pragma once

#include "bEngine/Core/Timestep.h"
#include "bEngine/Renderer/OrthographicCamera.h"
#include "bEngine/Events/ApplicationEvent.h"
#include "bEngine/Events/MouseEvent.h"

namespace bEngine
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, float moveSpeed, float rotationSpeed, bool rotate = false);

        void OnUpdate(Timestep timestep);
        void OnEvent(Event& e);
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        void SetZoomLevel(float level) { m_ZoomLevel = level; }
        float GetZoomLevel() const { return m_ZoomLevel; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
        
    private:
        constexpr static float MIN_ZOOM = 0.05f;
        constexpr static float MAX_ZOOM = 20.0f;
        
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        
        bool m_Rotate;

        float m_CameraTranslationSpeed;
        float m_CameraRotationSpeed;
        float m_CameraZoomSpeed{0.1f};
        
        float m_CameraRotation{0};
        glm::vec3 m_CameraPosition{0.0, 0.0, 0.0};
        OrthographicCamera m_Camera;
    };
}

