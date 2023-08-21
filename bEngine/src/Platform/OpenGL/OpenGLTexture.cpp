﻿#include "bepch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"


namespace bEngine
{
    OpenGLTexture2D::OpenGLTexture2D(std::string path)
        : m_Path(std::move(path))
    {
        int width, height, channelNum;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(m_Path.c_str(), &width, &height, &channelNum, 0);
        BE_CORE_ASSERT(data, "Failed to load image! {0}", stbi_failure_reason())
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channelNum == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else if (channelNum == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }

        BE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported.")

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }
}
