#include "trpch.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"
#include "Log.h"
#include "glad/glad.h"


namespace Trengine {
    VertexBuffer* VertexBuffer::Create(uint32_t size) {
        return Create(nullptr, size);
    }

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: 
            TR_CORE_ASSERT(false, "Renderer::None is not supported!");
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        TR_CORE_ASSERT(false, "Unknown RendererAPI");
        return NULL;
    }

    IndexBuffer* IndexBuffer::Create(unsigned int* indices, uint32_t size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            TR_CORE_ASSERT(false, "Renderer::None is not supported!");
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
        }

        TR_CORE_ASSERT(false, "Unknown RendererAPI");
        return NULL;
    }

    uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float: return GL_FLOAT;
    case ShaderDataType::Float2: return GL_FLOAT;
    case ShaderDataType::Float3: return GL_FLOAT;
    case ShaderDataType::Float4: return GL_FLOAT;
    case ShaderDataType::Mat3: return GL_FLOAT;
    case ShaderDataType::Mat4: return GL_FLOAT;
    case ShaderDataType::Int: return GL_INT;
    case ShaderDataType::Int2: return GL_INT;
    case ShaderDataType::Int3: return GL_INT;
    case ShaderDataType::Int4: return GL_INT;
    case ShaderDataType::Bool: return GL_BOOL;
    };

    TR_CORE_ASSERT(false, "Unknown Shader Data Type");
    return 0;
    }

    uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Float2: return 2 * 4;
        case ShaderDataType::Float3: return 3 * 4;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Mat3: return 3 * 3 * 4;
        case ShaderDataType::Mat4: return 4 * 4 * 4;
        case ShaderDataType::Int: return 4;
        case ShaderDataType::Int2: return 4 * 2;
        case ShaderDataType::Int3: return 4 * 3;
        case ShaderDataType::Int4: return 4 * 4;
        case ShaderDataType::Bool: return 1;
        };

        TR_CORE_ASSERT(false, "Unknown Shader Data Type");
        return 0;
    }
}
