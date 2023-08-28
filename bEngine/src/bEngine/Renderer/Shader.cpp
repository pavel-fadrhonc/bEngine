#include "bepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace bEngine
{
	Ref<Shader> Shader::Create(std::string_view path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::APIType::None: return std::make_shared<VoidShader>();
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLShader>(path); 
		}

		BE_CORE_ASSERT(false, "Unsupported RenderAPI")
		return nullptr;
	}

	Ref<Shader> Shader::Create(std::string_view name, std::string_view path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::APIType::None: return std::make_shared<VoidShader>();
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLShader>(name, path); 
		}

		BE_CORE_ASSERT(false, "Unsupported RenderAPI")
		return nullptr;
	}

	Ref<Shader> Shader::Create(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::APIType::None: return std::make_shared<VoidShader>();
			case RendererAPI::APIType::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource); 
		}

		BE_CORE_ASSERT(false, "Unsupported RenderAPI")
		return nullptr;
	}

	std::string Shader::ExtractName(const std::string& filepath)
	{
		size_t nameStart = filepath.find_last_of("/\\") + 1;
		nameStart = nameStart != std::string::npos ? nameStart : 0;
		size_t nameEnd = filepath.rfind('.');
		nameEnd = nameEnd != std::string::npos ? nameEnd : filepath.size() - nameStart;

		return filepath.substr(nameStart, nameEnd - nameStart);
	}

	void ShaderLibrary::Add(const Ref<Shader>& s)
	{
		auto& name = s->GetName();
		Add(name, s);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& s)
	{
		BE_CORE_ASSERT(!Exists(name), "Shader already present in the library.")
		
		m_Shaders[name] = s; 
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shaderName = Shader::ExtractName(filepath);

		if (Exists(shaderName))
			return m_Shaders[shaderName];
		
		m_Shaders[shaderName] = Shader::Create(filepath);

		return m_Shaders[shaderName];
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		if (Exists(name))
			return m_Shaders[name];

		m_Shaders[name] = Shader::Create(filepath);
		
		return m_Shaders[name];
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) const
	{
		BE_CORE_ASSERT(Exists(name), "Shader does not exists in the library");
		
		return m_Shaders.at(name);
	}
}

