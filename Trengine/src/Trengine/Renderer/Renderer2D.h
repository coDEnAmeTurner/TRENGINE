#pragma once
#include <memory>
#include "Trengine/Renderer/OrthographicCamera.h"
#include "RendererAPI.h"
#include "Trengine/Renderer/VertexArray.h"
#include "Trengine/Renderer/Shader.h"
#include "Trengine/Renderer/Texture.h"

namespace Trengine {
	class Renderer2D
	{
	private:
		struct QuadVertex {
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texCoord;
			float texIndex; //texture's index in an array of textures
			float tilingFactor;
		};

		struct Renderer2DData {
			const uint32_t MaxQuads = 10000;
			const uint32_t MaxVertices = MaxQuads * 4;
			const uint32_t MaxIndices = MaxQuads * 6;
			static const uint32_t MaxTextureSlots = 32;
			
			uint32_t quadIndexCount = 0;

			std::shared_ptr<VertexArray> quadVertexArray;
			std::shared_ptr<VertexBuffer> quadVertexBuffer;

			std::shared_ptr<Shader> textureShader;
			std::shared_ptr<Texture2D> whiteTexture;
			
			QuadVertex* quadVertexBufferBase = nullptr;
			QuadVertex* quadVertexBufferPtr = nullptr;

			std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> textureSlots; 
			uint32_t textureSlotIndex = 1; //0 is white texture
		};

		static Renderer2DData* data;
	public: 
		static void init();
		static void shutDown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const float& tilingFactor);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const float& tilingFactor);

		static const Renderer2DData* getData() { return data; }
		static void setData(const std::shared_ptr<VertexArray>& quadVertexArray) {
			data->quadVertexArray = quadVertexArray;

		}

		static void setTextureShader(const std::shared_ptr<Shader>& textureShader) {
			data->textureShader = textureShader;
		}

		static void flush();

		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

	};

	inline Renderer2D::Renderer2DData* Renderer2D::data = new Renderer2D::Renderer2DData();


}
