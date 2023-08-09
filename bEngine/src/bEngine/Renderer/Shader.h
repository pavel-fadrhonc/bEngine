#pragma once
#include "glm/fwd.hpp"

namespace bEngine
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;
        
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
    };

    class VoidShader : public Shader
    {
    public:
        virtual void Bind() const override {}
        virtual void Unbind() const override  {}

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override {}
    };
}

