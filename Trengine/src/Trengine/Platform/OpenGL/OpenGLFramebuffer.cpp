#include "trpch.h"
#include "OpenGLFramebuffer.h"
#include "glad/glad.h"
#include "Log.h"

namespace Trengine {
    static const uint32_t MaxFramebufferSize = 8192;

    void OpenGLFramebuffer::Invalidate()
    {
        if (rendererID) {
            glDeleteFramebuffers(1, &rendererID);
            glDeleteTextures(1, &colorAttachment);
            glDeleteTextures(1, &depthAttachment);
        }

        glCreateFramebuffers(1, &rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D, colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specification.width, specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
        glBindTexture(GL_TEXTURE_2D, depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, specification.width, specification.height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);

        TR_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
    {
        if (width <= 0 || height <= 0 || width > MaxFramebufferSize || height > MaxFramebufferSize)
        {
            TR_CORE_WARN("Attempted to resize framebuffer to {0}, {1}", width, height);
            return;
        }

        specification.width = width;
        specification.height = height;

        Invalidate();
    }

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
        : Framebuffer(spec)
    {
        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &rendererID);
        glDeleteTextures(1, &colorAttachment);
        glDeleteTextures(1, &depthAttachment);
    }

    void Trengine::OpenGLFramebuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
        glViewport(0, 0, specification.width, specification.height);
    }

    void Trengine::OpenGLFramebuffer::unBind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    

}
