#include "trpch.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

void Trengine::OpenGLRendererAPI::setClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Trengine::OpenGLRendererAPI::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Trengine::OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
{
	uint32_t count = indexCount ? vertexArray->getIndexBuffer()->getCount() : indexCount;
	vertexArray->bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Trengine::OpenGLRendererAPI::init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void Trengine::OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

