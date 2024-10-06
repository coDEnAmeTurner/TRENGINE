#include "trpch.h"
#include "SubTexture2D.h"

namespace Trengine {
	SubTexture2D::SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
	{
		texCoords[0] = { min.x, min.y };
		texCoords[1] = { max.x, min.y };
		texCoords[2] = { max.x, max.y };
		texCoords[3] = { min.x, max.y };
		
		this->texture = texture;
	}

	std::shared_ptr<SubTexture2D> SubTexture2D::CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->getWidth(), (coords.y * cellSize.y) / texture->getHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->getWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->getHeight() };
		
		return std::shared_ptr<SubTexture2D>(new SubTexture2D(texture, min, max));
	}


}
