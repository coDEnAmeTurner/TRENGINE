#pragma once
#include <memory>
#include "Trengine/Scene/Camera.h"
#include "RendererAPI.h"
#include "Trengine/Renderer/VertexArray.h"
#include "Trengine/Renderer/Shader.h"
#include "Trengine/Renderer/SubTexture2D.h"

namespace Trengine {
	class Renderer2D
	{
	private:
		struct QuadVertex {
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texCoord;
			float texIndex;
		};

		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t getTotalVertexCount() { return QuadCount * 4; }
			uint32_t getTotalIndexCount() { return QuadCount * 6; }
		};

		struct Renderer2DData {
			static const uint32_t MaxQuads = 10000;
			static const uint32_t MaxVertices = MaxQuads * 4;
			static const uint32_t MaxIndices = MaxQuads * 6;
			static const uint32_t MaxTextureSlots = 32;

			std::shared_ptr<VertexArray> quadVertexArray;
			std::shared_ptr<VertexBuffer> quadVertexBuffer;
			std::shared_ptr<Shader> textureShader;
			std::shared_ptr<Texture2D> whiteTexture;
			std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> textureSlots;

			glm::vec4 QuadVertexPositions[4];

			
			uint32_t quadIndexCount = 0;
			QuadVertex* quadVertexBufferBase = nullptr;
			QuadVertex* quadVertexBufferPtr = nullptr;
			uint32_t textureSlotIndex = 1;
		};

		static Statistics stats;

		static Renderer2DData* data;

	public: 
		static void resetStats();
		static Statistics getStats();

		static void init();
		static void shutDown();

		static void beginScene(const Camera& camera, const glm::mat4& transform);
		static void endScene();

		static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void drawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec4& color = { 1, 1, 1, 1 });
		static void drawQuadSubTexture(const glm::mat4& transform, const std::shared_ptr<SubTexture2D>& subTexture, const glm::vec4& color = { 1, 1, 1, 1 });

		static const Renderer2DData* getData() { return data; }
		static void setData(const std::shared_ptr<VertexArray>& quadVertexArray) {
			data->quadVertexArray = quadVertexArray;

		}
		static void FlushAndReset();

		static void setTextureShader(const std::shared_ptr<Shader>& textureShader) {
			data->textureShader = textureShader;
		}

		static void flush();

		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

	};

	inline Renderer2D::Renderer2DData* Renderer2D::data = new Renderer2D::Renderer2DData();

	inline Renderer2D::Statistics Renderer2D::stats;
}
