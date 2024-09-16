#include "trpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace Trengine {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLVertexBuffer::bind() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void OpenGLVertexBuffer::unBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
	{
		this->layout = layout;
	}

	BufferLayout& OpenGLVertexBuffer::getLayout()
	{
		// TODO: insert return statement here
		return this->layout;
	}


	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, uint32_t count)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		this->count = count;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::unBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
