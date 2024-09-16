#include "trpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Trengine {
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::unBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		TR_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(rendererID);
		vertexBuffer->bind();

		const auto& layout = vertexBuffer->getLayout();

		uint32_t index = 0;

		for (const auto& element : vertexBuffer->getLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized,
				vertexBuffer->getLayout().getStride(),
				(const void*)element.offset
			);
			index++;

		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererID);

		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
	{
		// TODO: insert return statement here
		return this->vertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
	{
		// TODO: insert return statement here
		return this->indexBuffer;
	}





}
