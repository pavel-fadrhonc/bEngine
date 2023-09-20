﻿#pragma once

namespace bEngine
{
    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::None:      return 0;
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }

        BE_CORE_ASSERT(false, "Unknown shader data type.");
        return 0;
    }
    
    struct BufferElement
    {
        std::string Name;
        uint32_t Offset;
        uint32_t Size;
        ShaderDataType Type;
        bool Normalized;

        BufferElement()
        {}
        
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {}

        uint32_t GetElementCount() const
        {
            switch (Type)
            {
                case ShaderDataType::None:      return 0;
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
                case ShaderDataType::Mat3:      return 3 * 3;
                case ShaderDataType::Mat4:      return 4 * 4;
                case ShaderDataType::Int:       return 1;
                case ShaderDataType::Int2:      return 2;
                case ShaderDataType::Int3:      return 3;
                case ShaderDataType::Int4:      return 4;
                case ShaderDataType::Bool:      return 1;
            }

            BE_CORE_ASSERT(false, "Unknown shader data type.");
            return 0;
        }
    };
    
    class BufferLayout
    {
    public:
        BufferLayout() {}
        
        BufferLayout(const std::initializer_list<BufferElement>& list)
            : m_Elements(list)
        {
            CalculateOffsetsAndStride();
        }
        
        const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() {return m_Elements.begin();}
        std::vector<BufferElement>::iterator end() {return m_Elements.end();}

        std::vector<BufferElement>::const_iterator begin() const {return m_Elements.begin();}
        std::vector<BufferElement>::const_iterator end() const {return m_Elements.end();}
        
    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset{0};
            for (auto& elem : m_Elements)
            {
                elem.Offset = offset;
                offset += elem.Size;
            }
            m_Stride = offset;
        }
        
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride;
    };
    
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() { }
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetData(const void* data, uint32_t size) = 0;

        static Ref<VertexBuffer> Create(size_t size);
        static Ref<VertexBuffer> Create(float* vertices, size_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() { }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t* indices, size_t size);
    };

    class VoidBufferLayout : public BufferLayout
    {
        
    };
    
    class VoidVertexBuffer : public VertexBuffer
    {
        virtual void Bind() const override {}
        virtual void Unbind() const override {}
        
        virtual void SetLayout(const BufferLayout& layout) override {}
        virtual const BufferLayout& GetLayout() const override { return m_BufferLayout;}

        virtual void SetData(const void* data, uint32_t size) {}

    private:
        VoidBufferLayout m_BufferLayout;
    };

    class VoidIndexBuffer : public IndexBuffer
    {
        virtual void Bind() const override {}
        virtual void Unbind() const override {}

        virtual uint32_t GetCount() const override { return 0;}
    };
}

