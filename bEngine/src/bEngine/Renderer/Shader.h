#pragma once

#include <string>
#include <unordered_map>

#include "glm/fwd.hpp"

namespace bEngine
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(std::string_view path);
        static Ref<Shader> Create(std::string_view name, std::string_view path);
        static Ref<Shader> Create(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource);

        virtual void SetInt(std::string_view name, int value) const = 0;
        virtual void SetFloat1(std::string_view name, float value) const = 0;
        virtual void SetFloat2(std::string_view name, const glm::vec2& value) const = 0;
        virtual void SetFloat3(std::string_view name, const glm::vec3& value) const = 0;
        virtual void SetFloat4(std::string_view name, const glm::vec4& value) const = 0;

        virtual void SetMat3(std::string_view name, const glm::mat3& matrix) const = 0;
        virtual void SetMat4(std::string_view name, const glm::mat4& matrix) const = 0;
        
        static std::string ExtractName(const std::string& filepath);
    };

    class VoidShader : public Shader
    {
    public:
        virtual void Bind() const override {}
        virtual void Unbind() const override  {}

        virtual const std::string& GetName() const override {return m_Name;}

        virtual void SetInt(std::string_view name, int value) const override {}
        virtual void SetFloat1(std::string_view name, float value) const override {}
        virtual void SetFloat2(std::string_view name, const glm::vec2& value) const override {}
        virtual void SetFloat3(std::string_view name, const glm::vec3& value) const override {}
        virtual void SetFloat4(std::string_view name, const glm::vec4& value) const override {}

        virtual void SetMat3(std::string_view name, const glm::mat3& matrix) const override {}
        virtual void SetMat4(std::string_view name, const glm::mat4& matrix) const override {}

    private:
        std::string m_Name;
    };

    class ShaderLibrary
    {
    public:
        void Add(const Ref<Shader>& s);
        void Add(const std::string& name, const Ref<Shader>& s);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);

        Ref<Shader> Get(const std::string& name) const;

        bool Exists(const std::string& name) const { return m_Shaders.contains(name); }
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}

