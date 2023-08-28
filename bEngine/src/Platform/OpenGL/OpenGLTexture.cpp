#include "bepch.h"
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

        GLenum internalFormat = 0;
        if (channelNum == 3)
        {
            internalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        }
        else if (channelNum == 4)
        {
            internalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
        }

        BE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported.")

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height)
    {
        GLenum internalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        // auto data = CreateScope<char[]>(4 * width * height);
        // for (uint32_t i = 0; i < width * height; i+=4)
        // {
        //     data[i] = data[i+i] = data[i+2] = data[i+3] = UCHAR_MAX;
        // }
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        uint32_t bpc = m_DataFormat == GL_RGBA ? 4 : 3l
        BE_CORE_ASSERT(size == m_Width * m_Height * bpc, "Size of data must be the whole texture");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }
}
