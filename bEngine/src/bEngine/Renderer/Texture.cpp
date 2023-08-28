#include "bepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace bEngine
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
            case RendererAPI::APIType::None: return CreateRef<Texture2DVoid>(); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::OpenGL: return CreateRef<OpenGLTexture2D>(path);
            case RendererAPI::APIType::None: return CreateRef<Texture2DVoid>(); 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }
}
