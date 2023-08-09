#include "bepch.h"
#include "PerspectiveCamera.h"
#include "glm/fwd.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/gtc/quaternion.hpp"

namespace bEngine
{
    glm::mat4 PerspectiveCamera::GetProjectionMatrix()
    {
        if (m_ProjDirty)
            m_ProjectionMatrix = glm::perspectiveFov(m_FOV, m_Width, m_Height, m_NearPlane, m_FarPlane);

        return m_ProjectionMatrix;
    }

    glm::mat4 PerspectiveCamera::GetViewMatrix()
    {
        if (m_ViewDirty)
        {
            auto T = glm::translate(m_Position);
            auto R = glm::quat{ glm::radians(m_Rotation) };
            auto S = glm::scale(glm::vec3{1,1,1});

            m_ViewMatrix = glm::inverse(T * glm::mat4_cast(R) * S);
        }

        return m_ViewMatrix;
    }
}
