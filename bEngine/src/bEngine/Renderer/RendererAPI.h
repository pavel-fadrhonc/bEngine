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

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void Init() = 0;
        virtual void SetViewport(int x, int y, uint32_t width, uint32_t height) = 0;

        inline static APIType GetAPI() { return s_API; }
    private:
        static APIType s_API;
    };
}

