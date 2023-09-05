#pragma once
#include "OrthographicCamera.h"
#include "Shader.h"
#include "Texture.h"

namespace bEngine
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();
        
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size,
            Ref<Texture> texture, TextureShaderProperties textureShaderProperties = TextureShaderProperties::Default);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size,
            Ref<Texture> texture, TextureShaderProperties textureShaderProperties = TextureShaderProperties::Default);

        // rotated version are explicit since calculating rotation matrix represents a significant cost
        static void DrawQuadRotated(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuadRotated(const glm::vec2& position, float rotation, const glm::vec2& size,
            Ref<Texture> texture, TextureShaderProperties textureShaderProperties = TextureShaderProperties::Default);
        static void DrawQuadRotated(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuadRotated(const glm::vec3& position, float rotation, const glm::vec2& size,
            Ref<Texture> texture, TextureShaderProperties textureShaderProperties = TextureShaderProperties::Default);
    };
}

