#pragma once

#include "Trengine/Renderer/Framebuffer.h"

namespace Trengine {
	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer();

		// Inherited via Framebuffer
		void bind() const override;
		void unBind() const override;

		void Invalidate();

		virtual void resize(uint32_t width, uint32_t height) override;
	};
}