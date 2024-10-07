#pragma once

#include "Trengine/Renderer/Texture.h"	
#include "glad/glad.h"

namespace Trengine {
	class OpenGLTexture2D : public Texture2D {
	private:
		std::string path;
		uint32_t width, height;
		GLenum internalFormat, dataFormat;
		uint32_t rendererID;

	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return width; }
		virtual uint32_t getHeight() const override { return height; }
		virtual uint32_t getRendererId() const override { return rendererID; }

		virtual void bind(uint32_t slot) const override;

		virtual void setData(void* data, uint32_t size) override;

		/*bool operator == (const std::shared_ptr<Texture2D>& other) {

			return rendererID == (std::dynamic_pointer_cast<OpenGLTexture2D>(other))->rendererID;
		}*/

	};
}
