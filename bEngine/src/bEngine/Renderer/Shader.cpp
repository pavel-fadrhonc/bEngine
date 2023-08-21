#include "bepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace bEngine
{
	Shader* Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::APIType::None: return new VoidShader();
			case RendererAPI::APIType::OpenGL: return new OpenGLShader(path); 
		}

		BE_CORE_ASSERT(false, "Unsupported RenderAPI")
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::APIType::None: return new VoidShader();
			case RendererAPI::APIType::OpenGL: return new OpenGLShader(vertexSource, fragmentSource); 
		}

		BE_CORE_ASSERT(false, "Unsupported RenderAPI")
		return nullptr;
	}
}

