#include "trpch.h"
#include "Renderer2D.h"
#include "Trengine/Platform/OpenGL/OpenglShader.h"
#include "Trengine/Renderer/RenderCommand.h"
#include <glm/ext/matrix_transform.hpp>
#include <Trengine/Platform/OpenGL/OpenGLTexture.h>

namespace Trengine {
	void Renderer2D::resetStats()
	{
		memset(&stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::getStats() {
		return stats;
	}

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
			});

		data->quadVertexArray->addVertexBuffer(data->quadVertexBuffer);

		data->quadVertexBufferBase = new QuadVertex[data->MaxVertices];

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


		data->whiteTexture = Texture2D::create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		data->textureShader = std::shared_ptr<Shader>(Shader::create("assets/shaders/Texture.glsl"));
		int32_t samplers[data->MaxTextureSlots];
		for (uint32_t i = 0; i < data->MaxTextureSlots; i++) {
			samplers[i] = i;
		}
		((OpenGLShader*)data->textureShader.get())->setUniformIntArray("u_Textures", samplers, data->MaxTextureSlots);

		data->textureSlots[0] = data->whiteTexture;

		data->QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data->QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		data->QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		data->QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
		
	}

	void Renderer2D::shutDown() {
		delete data;
	}

	void Renderer2D::beginScene(const Camera& camera, const glm::mat4& transform)
	{
		glm::mat4 viewProjection = camera.getProjection() * glm::inverse(transform);

		OpenGLShader* textureShaderRef = (OpenGLShader*)data->textureShader.get();
		textureShaderRef->bind();
		textureShaderRef->setUniformMat4("u_ViewProjection", viewProjection);

		data->quadIndexCount = 0;
		data->quadVertexBufferPtr = data->quadVertexBufferBase;
	}

	void Renderer2D::endScene()
	{
		uint32_t dataSize = (uint8_t*)data->quadVertexBufferPtr - (uint8_t*)data->quadVertexBufferBase;
		data->quadVertexBuffer->setData(data->quadVertexBufferBase, dataSize);

		flush();
	}


	void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = {
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f}
		};

		if (data->quadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		for (size_t i = 0; i < quadVertexCount; i++) 
		{
			data->quadVertexBufferPtr->position = transform * data->QuadVertexPositions[i];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->texCoord = textureCoords[i];
			data->quadVertexBufferPtr->texIndex = 0.0f;
			data->quadVertexBufferPtr++;

		}

		data->quadIndexCount += 6;

		stats.QuadCount++;
	}

	void Renderer2D::drawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture,
		const glm::vec4& color)
	{
		constexpr size_t quadVertexCount = 4;
		
		if (data->quadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		glm::vec2 textureCoords[] = {
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f}
		};

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < data->textureSlotIndex; i++) {

			if (((OpenGLTexture2D*)data->textureSlots[i].get())->getRendererId() == ((OpenGLTexture2D*)texture.get())->getRendererId()) 
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			textureIndex = (float)data->textureSlotIndex;
			data->textureSlots[data->textureSlotIndex] = texture;
			data->textureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			data->quadVertexBufferPtr->position = transform * data->QuadVertexPositions[i];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->texCoord = textureCoords[i];
			data->quadVertexBufferPtr->texIndex = textureIndex;
			data->quadVertexBufferPtr++;

		}

		data->quadIndexCount += 6;

		stats.QuadCount++;
	}

	void Renderer2D::drawQuadSubTexture(const glm::mat4& transform, const std::shared_ptr<SubTexture2D>& subTexture, const glm::vec4& color)
	{
		constexpr size_t quadVertexCount = 4;

		if (data->quadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		const glm::vec2* textureCoords = subTexture->getTexCoords();
		const std::shared_ptr<Texture2D> texture = subTexture->getTexture();


		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < data->textureSlotIndex; i++) {

			if (((OpenGLTexture2D*)data->textureSlots[i].get())->getRendererId() == ((OpenGLTexture2D*)texture.get())->getRendererId())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			textureIndex = (float)data->textureSlotIndex;
			data->textureSlots[data->textureSlotIndex] = texture;
			data->textureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			data->quadVertexBufferPtr->position = transform * data->QuadVertexPositions[i];
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->texCoord = textureCoords[i];
			data->quadVertexBufferPtr->texIndex = textureIndex;
			data->quadVertexBufferPtr++;

		}

		data->quadIndexCount += 6;

		stats.QuadCount++;
	}

	void Renderer2D::FlushAndReset()
	{
		endScene();

		data->quadIndexCount = 0;
		data->quadVertexBufferPtr = data->quadVertexBufferBase;
		data->textureSlotIndex = 1;
	}

	void Renderer2D::flush() {

		for (uint32_t i = 0; i < data->textureSlotIndex; i++) {
			data->textureSlots[i]->bind(i);
		}

		RenderCommand::DrawIndexed(data->quadVertexArray, data->quadIndexCount);
		stats.DrawCalls++;
	}

}
