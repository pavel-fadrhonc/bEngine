#include "bepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace bEngine
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::APIType::OpenGL: return Ref<Texture2D>{new OpenGLTexture2D(path)};
            case RendererAPI::APIType::None: return Ref<Texture2D>{new Texture2DVoid()}; 
        }

        BE_CORE_ASSERT(false, "Unsupported RenderAPI")
        return nullptr;
    }
}
