#include "bepch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace bEngine
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
    
}
