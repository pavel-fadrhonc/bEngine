#pragma once
#include "bEngine/Renderer/Shader.h"

namespace bEngine
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);

        ~OpenGLShader() override {}
        
        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
        
    private:
        uint32_t m_RendererID;
    };
}

