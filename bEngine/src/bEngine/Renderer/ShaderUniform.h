#pragma once
#include "Shader.h"
#include "glm/fwd.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

namespace bEngine
{
    class ShaderUniform
    {
    public:
        virtual ~ShaderUniform() = default;

        ShaderUniform(Ref<Shader> shader, std::string name)
            : m_Shader(std::dynamic_pointer_cast<OpenGLShader>(shader)), m_Name(std::move((name)))
        {}

        virtual void SetUniform() const = 0;

    protected:
        Ref<OpenGLShader> m_Shader;
        std::string m_Name;
    };

    class Mat4ShaderUniform : public ShaderUniform
    {
    public:
        Mat4ShaderUniform(Ref<Shader> shader, std::string name, const glm::mat4& matrix)
            : ShaderUniform(shader, std::move(name)), m_Matrix(&matrix)
        {}

        void SetUniform() const override
        {
            m_Shader->UploadUniformMat4(m_Name, *m_Matrix);
        }

    private:
        const glm::mat4* m_Matrix;
    };

    class Float4ShaderUniform : public ShaderUniform
    {
    public:
        Float4ShaderUniform(Ref<Shader> shader, std::string name, const glm::vec4& vec)
            : ShaderUniform(shader, std::move(name)), m_Vector(&vec)
        {}

        void SetUniform() const override
        {
            m_Shader->UploadUniformFloat4(m_Name, *m_Vector);
        }

    private:
        const glm::vec4* m_Vector;
    };

    class Float3ShaderUniform : public ShaderUniform
    {
    public:
        Float3ShaderUniform(Ref<Shader> shader, std::string name, const glm::vec3& vec)
            : ShaderUniform(shader, std::move(name)), m_Vector(&vec)
        {}

        void SetUniform() const override
        {
            m_Shader->UploadUniformFloat3(m_Name, *m_Vector);
        }

    private:
        const glm::vec3* m_Vector;
    };

    class IntShaderUniform : public ShaderUniform
    {
    public:
        IntShaderUniform(Ref<Shader> shader, std::string name, int val)
            : ShaderUniform(shader, std::move(name)), m_Value(val)
        {}

        void SetUniform() const override
        {
            m_Shader->UploadUniformInt(m_Name, m_Value);
        }

    private:
        int m_Value;
    };
}

