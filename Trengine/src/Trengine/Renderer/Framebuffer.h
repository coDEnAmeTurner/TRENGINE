#pragma once
#include <memory>
#include <cstdint>

namespace Trengine {
	struct FramebufferSpecification {
		uint32_t width, height;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};

	class Framebuffer {
	protected:
		uint32_t rendererID;
		uint32_t colorAttachment, depthAttachment;
		FramebufferSpecification specification;
	public:
		Framebuffer(const FramebufferSpecification& spec) 
		{
			this->specification = spec;
		}
		virtual ~Framebuffer() {};

		virtual const FramebufferSpecification& getSpecification() { return specification; }
		virtual const uint32_t getColorAttachmentRendererID() { return colorAttachment; }

		static Framebuffer* create(const FramebufferSpecification& spec);

		virtual void bind() const = 0;
		virtual void unBind() const = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;
	};
}
