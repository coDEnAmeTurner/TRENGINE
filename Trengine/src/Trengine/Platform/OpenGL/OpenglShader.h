#pragma once
#include "Trengine/Renderer/Shader.h"
#include <unordered_map>
#include <vector>

typedef unsigned int GLenum;

typedef unsigned int GLuint;

namespace Trengine {

	class OpenGLShader : public Shader {
	private:
		std::string readFile(const std::string& filepath);
		GLenum shaderTypeFromString(const std::string& type);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& src);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::string extractName(std::string filepath);

		std::vector<GLuint> shaderIDs;
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);

		virtual void setUniformFloat(const std::string& name, float values) override;
		virtual void setUniformFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void setUniformInt(const std::string& name, int values) override;
		virtual void setUniformFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void setUniformFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void setUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void setUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void setUniformIntArray(const std::string& name, int* values, uint32_t count) override;
	};
}
