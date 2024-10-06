#pragma once

#include "Texture.h"
#include "glm/glm.hpp"

namespace Trengine {
	class SubTexture2D {
	private:
		std::shared_ptr<Texture2D> texture;

		glm::vec2 texCoords[4];
	public:
		SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const glm::vec2* getTexCoords() const { return texCoords; }
		const std::shared_ptr<Texture2D> getTexture() const { return texture; }

		static std::shared_ptr<SubTexture2D> CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1, 1});
	};
}