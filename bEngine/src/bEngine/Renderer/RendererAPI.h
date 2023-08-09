#pragma once
#include "VertexArray.h"
#include "glm/vec4.hpp"

namespace bEngine
{
    class RendererAPI
    {
    public:
        enum class APIType
        {
            None = 0,
            OpenGL = 1
        };

    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static APIType GetAPI() { return s_API; }
    private:
        static APIType s_API;
    };
}

