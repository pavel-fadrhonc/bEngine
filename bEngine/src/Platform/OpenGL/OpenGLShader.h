#pragma once

#include <glad/glad.h>
#include "bEngine/Renderer/Shader.h"
#include "glm/fwd.hpp"

namespace bEngine
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(std::string_view filepath);
        OpenGLShader(std::string_view name, std::string_view filepath);
        OpenGLShader(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource);

        ~OpenGLShader() override = default;
        
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const std::string& GetName() const override { return m_Name; }

        void SetInt(std::string_view name, int value) const override;
        void SetFloat1(std::string_view name, float value) const override;
        void SetFloat2(std::string_view name, const glm::vec2& value) const override;
        void SetFloat3(std::string_view name, const glm::vec3& value) const override;
        void SetFloat4(std::string_view name, const glm::vec4& value) const override;

        void SetMat3(std::string_view name, const glm::mat3& matrix) const override;
        void SetMat4(std::string_view name, const glm::mat4& matrix) const override;

    private:
        std::string ReadFile(std::string_view filepath);
        
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        uint32_t m_RendererID;
        std::string m_Name;
    };
}

