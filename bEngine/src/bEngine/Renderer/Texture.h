#pragma once

namespace bEngine
{
    class Texture
    {
    public:
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual ~Texture() = default;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
        public:
            static Ref<Texture2D> Create(const std::string& path);
    };

    class Texture2DVoid : public Texture2D
    {
        public:
            Texture2DVoid() {}
            ~Texture2DVoid() override = default;

            uint32_t GetWidth() const override { return 0; }
            uint32_t GetHeight() const override { return 0; }

            void Bind(uint32_t slot = 0) const override {}
    };
}

