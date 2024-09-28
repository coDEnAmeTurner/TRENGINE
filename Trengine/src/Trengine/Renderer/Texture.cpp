#include "trpch.h"
#include "Trengine/Renderer/Renderer.h"
#include "Trengine/Platform/OpenGL/OpenGLTexture.h"
#include "Log.h"

namespace Trengine {
    std::shared_ptr<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: TR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }

        TR_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    std::shared_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: TR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
        }

        TR_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}
