#pragma once

namespace bEngine
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Shader* Create(const std::string& path);
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
    };

    class VoidShader : public Shader
    {
    public:
        virtual void Bind() const override {}
        virtual void Unbind() const override  {}
    };
}

