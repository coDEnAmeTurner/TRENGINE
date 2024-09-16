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

void Trengine::OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

}
