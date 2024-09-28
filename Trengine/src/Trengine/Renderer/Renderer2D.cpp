#include "trpch.h"
#include "Renderer2D.h"
#include "Trengine/Platform/OpenGL/OpenglShader.h"
#include "Trengine/Renderer/RenderCommand.h"
#include <glm/ext/matrix_transform.hpp>

namespace Trengine {
	void Renderer2D::init()
	{
		data = new Renderer2DData();
		data->quadVertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());

		data->quadVertexBuffer.reset(VertexBuffer::Create(data->MaxVertices * sizeof(QuadVertex)));
		data->quadVertexBuffer->setLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ShaderDataType::Float, "a_TexIndex"},
			{ShaderDataType::Float, "a_TilingFactor"}
			});

		data->quadVertexArray->addVertexBuffer(data->quadVertexBuffer);

		uint32_t* quadIndices = new uint32_t[data->MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < data->MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
			
		}
		std::shared_ptr<IndexBuffer> quadIB = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(quadIndices, data->MaxIndices));
		data->quadVertexArray->addIndexBuffer(quadIB);
		delete[] quadIndices;

		data->quadVertexBufferBase = new QuadVertex[data->MaxVertices];

		data->whiteTexture = Texture2D::create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[data->MaxTextureSlots];
		for (uint32_t i = 0; i < data->MaxTextureSlots; i++)
			samplers[i] = i;

		data->textureShader = std::shared_ptr<Shader>(Shader::create("assets/shaders/Texture.glsl"));
		((OpenGLShader*)data->textureShader.get())->setUniformIntArray("u_Textures", samplers, data->MaxTextureSlots);

		data->textureSlots[0] = data->whiteTexture;
	}

	void Renderer2D::shutDown() {
		delete data;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		OpenGLShader* textureShaderRef = (OpenGLShader*)data->textureShader.get();
		textureShaderRef->bind();
		textureShaderRef->setUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		textureShaderRef->setUniformMat4("u_Transform", glm::mat4(1.0f));

		data->quadVertexBufferPtr = data->quadVertexBufferBase;
		data->quadIndexCount = 0;
	}

	void Renderer2D::endScene()
	{
		uint32_t dataSize = (uint8_t*)data->quadVertexBufferPtr - (uint8_t*)data->quadVertexBufferBase;
		data->quadVertexBuffer->setData(data->quadVertexBufferBase, dataSize);

		flush();
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad(position, size, data->whiteTexture, 1.0f);
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const float& tilingFactor)
	{
		drawQuad({ position.x, position.y, 0 }, size, texture, tilingFactor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, const float& tilingFactor)
	{
		OpenGLShader* s = (OpenGLShader*)data->textureShader.get();

		constexpr glm::vec4 color = { 1, 1, 1, 1 };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < data->textureSlotIndex; i++) 
		{
			if (*data->textureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)data->textureSlotIndex;
			data->textureSlots[data->textureSlotIndex] = texture;
			data->textureSlots[data->textureSlotIndex]->bind(data->textureSlotIndex);
			data->textureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s->setUniformMat4("u_Transform", transform);

		data->quadVertexBufferPtr->position = position;
		data->quadVertexBufferPtr->color = color;
		data->quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		data->quadVertexBufferPtr->texIndex = textureIndex;
		data->quadVertexBufferPtr->tilingFactor = tilingFactor;
		data->quadVertexBufferPtr++;

		data->quadVertexBufferPtr->position = { position.x + size.x, position.y, 0.0f };
		data->quadVertexBufferPtr->color = color;
		data->quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		data->quadVertexBufferPtr->texIndex = textureIndex;
		data->quadVertexBufferPtr->tilingFactor = tilingFactor;
		data->quadVertexBufferPtr++;

		data->quadVertexBufferPtr->position = { position.x + size.x, position.y + size.y, 0.0f };
		data->quadVertexBufferPtr->color = color;
		data->quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		data->quadVertexBufferPtr->texIndex = textureIndex;
		data->quadVertexBufferPtr->tilingFactor = tilingFactor;
		data->quadVertexBufferPtr++;

		data->quadVertexBufferPtr->position = { position.x , position.y + size.y, 0.0f };
		data->quadVertexBufferPtr->color = color;
		data->quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		data->quadVertexBufferPtr->texIndex = textureIndex;
		data->quadVertexBufferPtr->tilingFactor = tilingFactor;
		data->quadVertexBufferPtr++;

		data->quadIndexCount += 6;

	}

	void Renderer2D::flush() {
		RenderCommand::DrawIndexed(data->quadVertexArray, data->quadIndexCount);
	}

}
