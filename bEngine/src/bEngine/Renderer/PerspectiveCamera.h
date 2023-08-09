#pragma once
#include "glm/fwd.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/detail/type_vec3.hpp"

namespace bEngine
{
    class PerspectiveCamera
    {
    public:
        /**
         * \brief 
         * \param position World position of camera
         * \param rotation In degrees
         * \param fov Field of view in degrees
         * \param width 
         * \param height 
         * \param nearPlane How far from camera do we cull stuff
         * \param farPlane How near to camera do we cull stuff
         */
        PerspectiveCamera(glm::vec3 position, glm::vec3 rotation,
               float fov, float width, float height, float nearPlane = 0.1f, float farPlane = 100.0f)
            : m_FOV(fov), m_Width(width), m_Height(height), m_NearPlane(nearPlane), m_FarPlane(farPlane),
                m_AspectRatio(width / height), m_Position(position), m_Rotation(rotation)
        { }

        float GetFOV() const { return m_FOV; }
        void SetFOV(float fov) { m_FOV = fov; m_ProjDirty = true; }

        float GetAspectRatio() const { return m_AspectRatio; }

        float GetNearPlane() const { return m_NearPlane; }
        void SetNearPlane(float nearPlane) { m_NearPlane = nearPlane; m_ProjDirty = true; }

        float GetFarPlane() const { return m_FarPlane; }
        void SetFarPlane(float farPlane) { m_FarPlane = farPlane; m_ProjDirty = true; }

        float GetWidth() const { return m_Width; }
        void SetWidth(float width) { m_Width = width; m_AspectRatio = m_Width / m_Height; m_ProjDirty = true; }

        float GetHeight() const { return m_Height; }
        void SetHeight(float height) { m_Height = height; m_AspectRatio = m_Width / m_Height; m_ProjDirty = true; }

        glm::vec3 GetPosition() const { return m_Position; }
        void SetPosition(glm::vec3 position) { m_Position = position; m_ViewDirty = true; }

        glm::vec3 GetRotation() const { return m_Rotation; }
        void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; m_ViewDirty = true; }
        
        glm::mat4 GetProjectionMatrix();
        glm::mat4 GetViewMatrix();

    private:
        float m_FOV;
        float m_Width;
        float m_Height;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        glm::vec3 m_Position;
        glm::vec3 m_Rotation;

        bool m_ProjDirty{true};
        bool m_ViewDirty{true};
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
    };
}
