#include "trpch.h"
#include "VertexArray.h"
#include "Renderer2D.h"
#include "Trengine/Platform/OpenGL/OpenGLVertexArray.h"

namespace Trengine {
    VertexArray* VertexArray::Create()
    {
		switch (Renderer2D::GetAPI())
		{
		case RendererAPI::API::None: TR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		default:
			break;
		}

		TR_CORE_ASSERT(false, "Unknown RendererAPI");

		return nullptr;
    }

}
