#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace bEngine
{
    class Texture
    {
    public:
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual ~Texture() = default;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
        public:
            static Ref<Texture2D> Create(uint32_t width, uint32_t height);
            static Ref<Texture2D> Create(const std::string& path);
    };

    class Texture2DVoid : public Texture2D
    {
        public:
            Texture2DVoid() {}
            ~Texture2DVoid() override = default;

            uint32_t GetWidth() const override { return 0; }
            uint32_t GetHeight() const override { return 0; }
        
            void SetData(void* data, uint32_t size) override {};

            void Bind(uint32_t slot = 0) const override {}
    };

    struct TextureShaderProperties
    {
        glm::vec2 Tiling {1.0, 1.0};
        glm::vec2 Offset {0.0, 0.0};
        glm::vec4 Color {1.0, 1.0, 1.0, 1.0};

        const static TextureShaderProperties Default;
    };
}

