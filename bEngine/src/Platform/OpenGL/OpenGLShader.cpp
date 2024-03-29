﻿#include "bepch.h"
#include "fstream"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include "glm/gtc/type_ptr.hpp"

namespace bEngine
{
	static GLenum ShaderTypeFromString(std::string_view type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		BE_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}
	
	OpenGLShader::OpenGLShader(std::string_view filepath)
		: m_Name(ExtractName(filepath.data()))
	{
		BE_PROFILE_FUNCTION();
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view filepath)
		: m_Name(name)
	{
		BE_PROFILE_FUNCTION();
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource)
	    : m_Name(name)
    {
		BE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;

		Compile(sources);
    }

    void OpenGLShader::Bind() const
    {
		BE_PROFILE_FUNCTION();
    	glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    { 
    	glUseProgram(0);
    }

    void OpenGLShader::SetInt(std::string_view name, int value) const
    {
		BE_PROFILE_FUNCTION();
    	GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
    	{
    		BE_CORE_WARN("Uniform '{0}' not found!", name);
    		return;
    	}
    	glUniform1i(location, value);    	
    }

    void OpenGLShader::SetFloat1(std::string_view name, const float value) const
    {
		BE_PROFILE_FUNCTION();
    	GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
    	{
    		BE_CORE_WARN("Uniform '{0}' not found!", name);
    		return;
    	}
    	glUniform1f(location, value);    	
    }

    void OpenGLShader::SetFloat2(std::string_view name, const glm::vec2& value) const
    {
		BE_PROFILE_FUNCTION();
    	GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
    	{
    		BE_CORE_WARN("Uniform '{0}' not found!", name);
    		return;
    	}
    	glUniform2fv(location, 1, glm::value_ptr(value));
    }

	void OpenGLShader::SetFloat3(std::string_view name, const glm::vec3& value) const
    {
		BE_PROFILE_FUNCTION();
    	GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
    	{
    		BE_CORE_WARN("Uniform '{0}' not found!", name);
    		return;
    	}
    	glUniform3fv(location, 1, glm::value_ptr(value));
    }

	void OpenGLShader::SetFloat4(std::string_view name, const glm::vec4& value) const
    {
		BE_PROFILE_FUNCTION();
    	GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
    	{
    		BE_CORE_WARN("Uniform '{0}' not found!", name);
    		return;
    	}
    	glUniform4fv(location, 1, glm::value_ptr(value));
    }

	void OpenGLShader::SetMat3(std::string_view name, const glm::mat3& matrix) const
    {
		BE_PROFILE_FUNCTION();
    	GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
    	{
    		BE_CORE_WARN("Uniform '{0}' not found!", name);
    		return;
    	}
    	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

	void OpenGLShader::SetMat4(std::string_view name, const glm::mat4& matrix) const
    {
		BE_PROFILE_FUNCTION();
	    GLint location = glGetUniformLocation(m_RendererID, name.data());
    	if (location == -1)
		{
			BE_CORE_WARN("Uniform '{0}' not found!", name);
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

	std::string OpenGLShader::ReadFile(std::string_view filepath)
	{
		BE_PROFILE_FUNCTION();
		std::string result;
		std::ifstream in(filepath.data(), std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			BE_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		BE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			BE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			BE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
		BE_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();
		BE_CORE_ASSERT(shaderSources.size() <= 2, "Max 2 shaders supported.")
		std::array<GLenum, 2> glShaderIDs;

		int glShaderIdIndex = 0;
		for (const auto& [shaderType, source] : shaderSources)
		{
			GLuint shader = glCreateShader(shaderType);

			const auto* psource = source.c_str();
			glShaderSource(shader, 1, &psource, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if(isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			
				glDeleteShader(shader);

				BE_CORE_ERROR("{0}", infoLog.data());
				BE_CORE_ASSERT(false, "Shader compilation failure!")
			
				break;
			}
			
			glAttachShader(program, shader);
			glShaderIDs[glShaderIdIndex++] = shader;
			
			glLinkProgram(program);

			// Note the different functions here: glGetProgram* instead of glGetShader*.
			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
				
				// We don't need the program anymore.
				glDeleteProgram(program);
				// Don't leak shaders either.
				for(auto shaderId : glShaderIDs)
				{
					glDeleteShader(shaderId);	
				}

				// Use the infoLog as you see fit.
				BE_CORE_ERROR("{0}", infoLog.data());
				BE_CORE_ASSERT(false, "Shader link failure!")
				
				// In this simple program, we'll just leave
				return;
			}
		}

		// Always detach shaders after a successful link.
		for(auto shaderId : glShaderIDs)
		{
			glDetachShader(program, shaderId);	
		}

		m_RendererID = program;
    }
}
