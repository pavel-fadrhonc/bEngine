#pragma once

#include <string>
#include <unordered_map>

namespace bEngine
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& path);
        static Ref<Shader> Create(const std::string& name, const std::string& path);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

        static std::string ExtractName(const std::string& filepath);
    };

    class VoidShader : public Shader
    {
    public:
        virtual void Bind() const override {}
        virtual void Unbind() const override  {}

        virtual const std::string& GetName() const override {return m_Name;}

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

