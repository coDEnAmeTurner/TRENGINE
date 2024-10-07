#include "trpch.h"
#include "Renderer2D.h"
#include "Trengine/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Trengine {
    Framebuffer* Framebuffer::create(const FramebufferSpecification& spec)
    {
		switch (Renderer2D::GetAPI())
		{
		case RendererAPI::API::None: TR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL: return new OpenGLFramebuffer(spec);
		default:
			break;
		}

		TR_CORE_ASSERT(false, "Unknown RendererAPI");

		return nullptr;
    }

}
